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
	if (split == NULL)
		return ;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	split = NULL;
}

void	free_args(char **args)// IN CASE IT IS NEEDED
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free (args);
}

void	free_and_nullify(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_struct_fields(t_main *parsed_struct)
{
	free_and_nullify((void **)&parsed_struct->cmd);
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

void	free_parsed_struct(t_main *parsed_struct, int num_commands)
{
	int	i;

	i = 0;
	while ((parsed_struct) && (i < num_commands))
	{
		free_struct_fields(&parsed_struct[i]);
		i++;
	}
	free(parsed_struct);
}
