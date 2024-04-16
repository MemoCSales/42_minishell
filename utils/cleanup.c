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

void	cleanup_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void	free_main(t_main *main_var)
{
	int	i;
	int	j;

	i = 0;
	while (main_var[i].cmd != NULL)
	{
		free(main_var[i].cmd);
		if(main_var[i].args != NULL)
		{
			j = 0;
			while(main_var[i].args[j] != NULL)
			{
				free(main_var[i].args[j]);
				j++;
			}
			free(main_var[i].args);
		}
		if (main_var[i].flags != NULL)
		{
			free(main_var[i].flags);
		}
		i++;
	}
	free(main_var);
}
