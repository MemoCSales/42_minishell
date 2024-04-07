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

void	unset_buildin(t_env *env_vars, char *var_name)
{
	int	index;
	int	i;

	index = -1;
	if (var_name == NULL)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return ;
	}
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
		printf("ENV_VAR [%s] deleted\n", var_name); //printf for testing, might delete later
		env_buildin(env_vars);						//can delete later
	}
}

int	find_index(t_env *env_vars, char *var_name)
{
	int	i;
	int	index;

	i = 0;
	index = -1;
	while (env_vars->env_vars[i] != NULL) //loop to find thei ndex of the environment var in the env_var->env_vars
	{
		if (ft_strncmp(env_vars->env_vars[i], var_name, ft_strlen(var_name)) == 0 \
			&& env_vars->env_vars[i][ft_strlen(var_name)] == '=')
		{
			index = i;
			break;
		}
		i++;
	}
	return (index);
}
