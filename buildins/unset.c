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
	int	index;
	int	i;

	index = -1;
	if (var_name == NULL)
		return (0);
	index = find_index(env_vars, var_name);
	if (index != -1)
	{
		free(env_vars->env_vars[index]);
		i = index;
		while (env_vars->env_vars[i] != NULL)
		{
			env_vars->env_vars[i] = env_vars->env_vars[i + 1];
			i++;
		}
	}
	return (0);
}

int	find_index(t_env *env_vars, char *var_name)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (env_vars->env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars->env_vars[i], var_name,
				ft_strlen(var_name)) == 0
			&& env_vars->env_vars[i][ft_strlen(var_name)] == '=')
		{
			index = i;
			break ;
		}
		i++;
	}
	return (index);
}
