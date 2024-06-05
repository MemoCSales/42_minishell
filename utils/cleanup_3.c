/* ************************************************************************** */
/*                                                                            */
/*   cleanup_3.c                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_parse_struct_without_cmds(t_main *parsed_struct)
{
	if ((parsed_struct->input_file != NULL || parsed_struct->output_file != NULL
			|| parsed_struct->heredoc != NULL || parsed_struct->extra != NULL))
	{
		if (parsed_struct->flags)
			free_and_nullify((void **)&parsed_struct->flags);
		if (parsed_struct->args)
			cleanup_env_var(&parsed_struct->args);
		free_and_nullify((void **)&parsed_struct->input_file);
		free_and_nullify((void **)&parsed_struct->output_file);
		free_and_nullify((void **)&parsed_struct->heredoc);
		free_and_nullify((void **)&parsed_struct->extra);
		free_and_nullify((void **)&parsed_struct->current_dir);
		if (parsed_struct->fd[0] != -1)
		{
			close(parsed_struct->fd[0]);
			parsed_struct->fd[0] = -1;
		}
		if (parsed_struct->fd[1] != -1)
		{
			close(parsed_struct->fd[1]);
			parsed_struct->fd[1] = -1;
		}
	}
	free(parsed_struct);
}

void	free_main(t_main *main_var)
{
	int	i;
	int	j;

	i = 0;
	while (main_var[i].cmd != NULL)
	{
		free(main_var[i].cmd);
		if (main_var[i].args != NULL)
		{
			j = 0;
			while (main_var[i].args[j] != NULL)
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
