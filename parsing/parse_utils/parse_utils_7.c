/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_7.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_flags(t_main *command, char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		command->flags = args[1];
		command->args = copy_args(&args[2]);
	}
	else
	{
		command->flags = NULL;
		command->args = copy_args(&args[1]);
	}
}

void	create_pipe(t_main *command, int i, int num_commands)
{
	if (i < num_commands - 1)
	{
		if (pipe(command -> fd) == -1)
		{
			perror("Pipe error");
			exit(EXIT_FAILURE);
		}
	}
}

void	handle_redirections(t_main *parsed_struct, char **args, int i)
{
	int	j;

	j = 0;
	while (args[j] != NULL)
	{
		if (check_redir(args, j))
		{
			redirection(parsed_struct, args, i, j);
			j--;
		}
		j++;
	}
}
