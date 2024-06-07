/* ************************************************************************** */
/*                                                                            */
/*   general_utils_2.c          ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_new_var(char *var_name, char *new_value)
{
	size_t	var_name_len;
	char	*new_var;

	var_name_len = ft_strlen(var_name);
	new_var = malloc(var_name_len + ft_strlen(new_value) + 2);
	if (!new_var)
	{
		ft_putstr_fd("Error allocating memory for new_value\n", 2);
		return (NULL);
	}
	ft_memcpy(new_var, var_name, var_name_len);
	new_var[var_name_len] = '=';
	ft_strcpy_memo(new_var + var_name_len + 1, new_value);
	new_var[var_name_len + ft_strlen(new_value) + 1] = '\0';
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
		ft_putstr_fd("ψΨ: cd: too many arguments\n", STDERR_FILENO);
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

char	**split_cmd_path(char *cmd_path)
{
	char	**dir_paths;

	dir_paths = ft_split(cmd_path, ':');
	if (!cmd_path)
	{
		cleanup_split(dir_paths);
		return (NULL);
	}
	return (dir_paths);
}
