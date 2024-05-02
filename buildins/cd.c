/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:37:46 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/04/02 13:37:47 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy(char *dst, char *src)
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
	ft_strcpy(new_var + var_name_len + 1, new_value);
	i = 0;
	while (env->env_vars[i])
	{
		if (ft_strncmp(env->env_vars[i], var_name, var_name_len) == 0 && env->env_vars[i][var_name_len] == '=')
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

int cd_builtin(t_env *env_vars, char *path)
{
	int 	status;
	char 	*home;
	char 	*prev_dir;
	char	*curr_dir;

	errno = 0;
	home = getenv("HOME");
	prev_dir = NULL;
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
			ft_putstr_fd("cd: HOME environment variable not set\n", STDERR_FILENO);
		path = home;
	}
	else if (strcmp(path, "..") == 0)
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
			ft_putstr_fd("cd: No such file or directory: ", STDERR_FILENO);
			printf("%s\n", path);
		}
		if (prev_dir != NULL)
			free(prev_dir);
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
