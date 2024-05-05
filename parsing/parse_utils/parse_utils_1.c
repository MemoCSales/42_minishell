/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_1.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// INITIALIZERS
t_main	*initialize_main(t_main *main_var, int num_commands)
{
	if (num_commands <= 0)
	{
		ft_putstr_fd("Error: Invalid number of commands\n", 2);
		exit (1);
	}
	// if (!main_var)
	// {
	// 	ft_putstr_fd("Error: main_var is NULL\n", 2);
	// 	exit(1);
	// }
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	if (!main_var)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit (1);
	}
	main_var->cmd = NULL;
	main_var->flags = NULL;
	main_var->args = NULL;
	main_var->input_file = NULL;
	main_var->output_file = NULL;
	main_var->heredoc = NULL;
	return (main_var);
}

//PARSERS
char	*read_heredoc(char *delimiter)
{
	char	*heredoc;
	char	*line;
	// char	*temp;

	heredoc = NULL;
	if (!delimiter)
	{
		ft_putstr_fd("Error: No delimiter specified\n", STDERR_FILENO);
		return (NULL);
	}
	line = loop_heredoc(delimiter, heredoc);
	free (line);
	printf("SAIU DO HEREDOC\n");
	return (heredoc);
}

char	*loop_heredoc(char *delimiter, char *heredoc)
{
	char	*line;
	char	*temp;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free (line);
			break ;
		}
		temp = ft_strjoin(heredoc, line);
		free (heredoc);
		heredoc = ft_strjoin(temp, "\n");
		free (temp);
		free (line);
	}
	return (heredoc);
}

// main_var->fd[0] = 0; // main_var->fd[1] = 0;
// main_var->pid = 0;
