/* ************************************************************************** */
/*                                                                            */
/*   cleanup_2.c                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_args_2(char ***args)
{
	int	j;

	j = 0;
	if (*args)
	{
		while ((*args)[j])
		{
			free_and_nullify((void **)&(*args)[j]);
			j++;
		}
	}
	free_and_nullify((void **)args);
}

void	free_main_struct(t_main *main_var)
{
	int	i;

	i = 0;
	while (i < main_var->num_cmds)
	{
		if (main_var[i].cmd)
			free(main_var[i].cmd);
		if (main_var[i].flags)
			free(main_var[i].flags);
		if (main_var[i].args)
			cleanup_split(main_var[i].args);
		if (main_var[i].input_file)
			free(main_var[i].input_file);
		if (main_var[i].output_file)
			free(main_var[i].output_file);
		if (main_var[i].heredoc)
			free(main_var[i].heredoc);
		if (main_var[i].extra)
			free(main_var[i].extra);
		if (main_var[i].current_dir)
			free(main_var[i].current_dir);
		i++;
	}
	// free(main_var);
}

void	free_ph_strings(char ***ph_strings)
{
	int	i;

	i = 0;
	while ((*ph_strings)[i] != NULL)
	{
		free((*ph_strings)[i]);
		i++;
	}
	free(*ph_strings);
}

void	free_string(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
	{
		free(string);
		i++;
	}
}

