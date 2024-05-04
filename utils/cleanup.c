/* ************************************************************************** */
/*                                                                            */
/*   cleanup.c                  ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
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

void free_args(char **args)// IN CASE IT IS NEEDED
{
    int i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}