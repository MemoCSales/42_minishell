/* ************************************************************************** */
/*                                                                            */
/*   unset.c                    ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_builtin(t_env *env_vars, char *var_name)
{
	char	**new_env;
	int		index;
	int		len;

	if (var_name == NULL)
		return (0);
	index = find_index(env_vars, var_name);
	if (index == -1)
		return (0);
	free(env_vars->env_vars[index]);
	len = 0;
	while (env_vars->env_vars[len] != NULL)
		len++;
	shift_env_vars(env_vars->env_vars, index);
	env_vars->env_vars[len - 1] = NULL;
	new_env = realloc_new_env(env_vars->env_vars, len - 1);
	if (!new_env)
	{
		ft_putstr_fd("Unset: Error: Unable to allocate memory\n", 2);
		return (1);
	}
	env_vars->env_vars = new_env;
	return (0);
}

void	shift_env_vars(char **env_vars, int index)
{
	int	i;

	i = index;
	while (env_vars[i] != NULL)
	{
		env_vars[i] = env_vars[i + 1];
		i++;
	}
}

char	**realloc_new_env(char **env_vars, int len)
{
	char	**new_env;
	int		i;

	new_env = calloc((len + 1), sizeof(char *));
	if (!new_env)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_env[i] = env_vars[i];
		i++;
	}
	new_env[len] = NULL;
	free(env_vars);
	return (new_env);
}

int	find_index(t_env *env_vars, char *var_name)
{
	int	i;

	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars->env_vars[i], var_name,
				ft_strlen(var_name)) == 0
			&& env_vars->env_vars[i][ft_strlen(var_name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}
