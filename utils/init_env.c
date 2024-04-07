/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env(t_env *env_vars, char **env)
{
	int	num_vars;
	int	i;

	num_vars = 0;
	while (env[num_vars] != NULL)
		num_vars++;
	env_vars->env_vars = (char **)malloc((num_vars + 1) * sizeof(char *));
	if (!env_vars->env_vars)
	{
		env_vars->status = -1;
		return ;
	}
	i = 0;
	while (i < num_vars)
	{
		env_vars->env_vars[i] = ft_strdup(env[i]);
		i++;
	}
	env_vars->status = 0;
}

void	check_env(t_env *env_vars)
{
	int	i;

	if (env_vars->status == 0)
	{
		i = 0;
		while (env_vars->env_vars[i] != NULL)
		{
			printf("%s\n", env_vars->env_vars[i]);
			i++;
		}
		i = 0;
		while (env_vars->env_vars[i] != NULL)
		{
			free(env_vars->env_vars[i]);
			i++;
		}
		free(env_vars->env_vars);
	}
	else
		printf("Error initializaing environment variables\n");
}
