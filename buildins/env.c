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

void env_buildin(t_env *env_vars)
{
	int	i;

	if (env_vars->env_vars == NULL)
	{
		printf("No environment variables available.\n");
		return ;
	}
	i = 0;
	while (env_vars->env_vars[i] != NULL)
	{
		printf("%s\n", env_vars->env_vars[i]);
		i++;
	}
}
