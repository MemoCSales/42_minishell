/* ************************************************************************** */
/*                                                                            */
/*   cd.c                       ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy_memo(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*create_new_var(char *var_name, char *new_value)
{
	size_t	var_name_len;
	char	*new_var;

	var_name_len = ft_strlen(var_name);
	new_var = malloc(var_name_len + ft_strlen(new_value));
	if (!new_var)
	{
		ft_putstr_fd("Error allocating memory for new_value\n", 2);
		return (NULL);
	}
	ft_memcpy(new_var, var_name, var_name_len);
	new_var[var_name_len] = '=';
	ft_strcpy_memo(new_var + var_name_len + 1, new_value);
	return (new_var);
}

void	find_and_replace_var(t_env *env, char *var_name, char *new_var)
{
	int		i;
	size_t	var_name_len;

	i = 0;
	var_name_len = ft_strlen(var_name);
	while (env->env_vars[i])
	{
		if (ft_strncmp(env->env_vars[i], var_name, var_name_len) == 0
			&& env->env_vars[i][var_name_len] == '=')
		{
			free(env->env_vars[i]);
			env->env_vars[i] = new_var;
			return ;
		}
		i++;
	}
	env->env_vars[i] = new_var;
	env->env_vars[i + 1] = NULL;
}

void	update_env_var(t_env *env, char *var_name, char *new_value)
{
	char	*new_var;

	new_var = create_new_var(var_name, new_value);
	if (new_var != NULL)
		find_and_replace_var(env, var_name, new_var);
}

/*This function will handle the logic of determining the path to change
to based on the arguments and environment variables.*/
char	*get_path(t_main *main, char *path)
{
	char	*home;

	home = getenv("HOME");
	if (main->args[0] == NULL || ft_strcmp(main->args[1], " ") == 0)
		return (home);
	if (main->args[0] && main->args[1] != NULL)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
			ft_putstr_fd("cd: HOME environment variable not set\n",
				STDERR_FILENO);
		return (home);
	}
	else if (ft_strcmp(path, "..") == 0)
		return ("..");
	return (path);
}

/*This function will handle the actual changing of
the directory and updating of the main->current_dir variable.*/
int	change_directory(t_main *main, char *path)
{
	int		status;
	char	*home;

	status = chdir(path);
	if (status == 0)
	{
		free(main->current_dir);
		main->current_dir = getcwd(NULL, 0);
		if (main->current_dir == NULL)
		{
			home = getenv("HOME");
			chdir(home);
			main->current_dir = ft_strdup(home);
		}
	}
	return (status);
}

/* This function will handle the updating of the environment variables.*/
void	update_env(t_env *env_vars, char *prev_dir, t_main *main)
{
	if (prev_dir != NULL)
		update_env_var(env_vars, "OLDPWD", prev_dir);
	if (main->current_dir != NULL)
		update_env_var(env_vars, "PWD", main->current_dir);
}

char	*get_prev_dir(t_main *main, int *flag_free)
{
	char	*prev_dir;

	if (main->current_dir != NULL)
	{
		prev_dir = ft_strdup(main->current_dir);
		*flag_free = 1;
	}
	else
		prev_dir = getenv("HOME");
	return (prev_dir);
}

char	*handle_path(t_main *main, char *path, char *prev_dir, int *flag_free)
{
	path = get_path(main, path);
	if (path == NULL && *flag_free)
	{
		free(prev_dir);
		prev_dir = NULL;
	}
	return (path);
}

int	cd_builtin(t_env *env_vars, char *path, t_main *main)
{
	int		status;
	int		flag_free;
	char	*prev_dir;

	flag_free = 0;
	prev_dir = get_prev_dir(main, &flag_free);
	path = handle_path(main, path, prev_dir, &flag_free);
	if (path == NULL)
		return (1);
	status = change_directory(main, path);
	if (status == 0)
		update_env(env_vars, prev_dir, main);
	else
		cd_error_check(path);
	if (flag_free)
	{
		free(prev_dir);
		prev_dir = NULL;
	}
	if (status == 0)
		return (0);
	else
		return (1);
}

void	cd_error_check(char *path)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("cd: Permission denied: ", STDERR_FILENO);
		printf("%s\n", path);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("bash: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
}
