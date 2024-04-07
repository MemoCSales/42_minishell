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

void	export_buildin(t_env *env_vars, char *new_var)
{
	int		i;
	int		j;
	char	**new_env_vars;

	if (check_duplicate(env_vars, new_var))
		return;
	i = 0;
	while (env_vars->env_vars[i] != NULL)
		i++;
	new_env_vars = malloc((i + 2) * sizeof(char *));
	if (!new_env_vars)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", 2);
		return ;
	}
	j = 0;
	while (j < i)
	{
		new_env_vars[j] = env_vars->env_vars[j];
		j++;
	}
	new_env_vars[i] = ft_strdup(new_var);
	new_env_vars[i + 1] = NULL;
	free(env_vars->env_vars);
	env_vars->env_vars = new_env_vars;
	env_buildin(env_vars);	//can delete later
}

int	check_duplicate(t_env *env_vars, char *new_var)
{
	int	i;

	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		if (ft_strncmp(env_vars->env_vars[i], new_var, ft_strlen(new_var)) == 0 \
			&& env_vars->env_vars[i][ft_strlen(new_var)] == '=')
		{
			free(env_vars->env_vars[i]);
			env_vars->env_vars[i] = ft_strdup(new_var);
			if(!env_vars->env_vars[i])
				ft_putstr_fd("Error: Unable to duplicate string\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}
