/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_2.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(char **args, int j)
{
	if (ft_strcmp(args[j], ">>") == 0
		|| ft_strcmp(args[j], "<<") == 0
		|| ft_strcmp(args[j], "<") == 0
		|| ft_strcmp(args[j], ">") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	redirection(t_main *parsed_struct, char **args, int i, int j)
{
	char	*delimiter;
	char	*heredoc;

	heredoc = NULL;
	if (ft_strcmp(args[j], ">>") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
		parsed_struct[i].extra = ft_strdup(args[j]);
	}
	else if (ft_strcmp(args[j], "<<") == 0 && args[j + 1])
	{
		delimiter = args[j + 1];
		heredoc = read_heredoc(delimiter);
		parsed_struct[i].heredoc = heredoc;
	}
	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
	{
		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
	}
	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
	}
	remove_args(args, j, 2);
}

void	check_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	copy_increment(char *prepared, const char *line, int *i, int *j)
{
	prepared[*j] = line[*i];
	(*i)++;
	(*j)++;
}
