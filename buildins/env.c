/* ************************************************************************** */
/*                                                                            */
/*   env.c                      ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_builtin(t_env *env_vars)
{
	int	i;

	if (env_vars->env_vars == NULL)
	{
		printf("No environment variables available.\n");
		return (1);
	}
	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		ft_putstr_fd(env_vars->env_vars[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}
