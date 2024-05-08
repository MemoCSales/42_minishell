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

void	update_env_var(t_env *env, char *var_name, char *new_value)
{
	int		i;
	char	*new_var;
	size_t	var_name_len;

	var_name_len = ft_strlen(var_name);
	new_var = malloc(var_name_len + ft_strlen(new_value) + 2);
	if (!new_var)
	{
		ft_putstr_fd("Error allocating memory for new_var\n", 2);
		return ;
	}
	// Construct the new value
	ft_memcpy(new_var, var_name, var_name_len);
	new_var[var_name_len] = '=';
	ft_strcpy_memo(new_var + var_name_len + 1, new_value);
	i = 0;
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
	// If Variable not founc add it to the end of the env_vars array
	env->env_vars[i] = new_var;
	env->env_vars[i + 1] = NULL;
}

int cd_builtin(t_env *env_vars, char *path, t_main *main)
{
	int		status;
	char	*home;
	char	*prev_dir;
	char	*curr_dir;

	errno = 0;
	home = getenv("HOME");
	prev_dir = NULL;
	curr_dir = NULL;
	if (main->args[0] == NULL || ft_strcmp(main->args[1], " ") == 0)
	{
		// printf("%s\n", main->args[0]);
		path = home;
	}
	if (main->args[0] && main->args[1] != NULL)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
		{
			ft_putstr_fd("cd: HOME environment variable not set\n",
				STDERR_FILENO);
		}
		path = home;
	}
	else if (ft_strcmp(path, "..") == 0)
		path = "..";
	prev_dir = getcwd(NULL, 0); // Save current directory
	status = chdir(path);
	if (status == 0)
	{
		curr_dir = getcwd(NULL, 0);
		update_env_var(env_vars, "OLDPWD", prev_dir);
		update_env_var(env_vars, "PWD", curr_dir);
	}
	else
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
	if (prev_dir != NULL)
		free(prev_dir);
	if (curr_dir != NULL)
		free(curr_dir);
	if (status == 0)
		return (0);
	else
		return (1);
}
