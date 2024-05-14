/* ************************************************************************** */
/*                                                                            */
/*   6_pipe_and_redirection.c   ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_quotes(char *delimiter)
{
	char	*quotes;
	char	*line;
	char	*temp;

	quotes = NULL;
	if (check_delimiter(delimiter))
		return (NULL);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break ;
		temp = quotes;
		if (quotes)
			quotes = ft_strjoin(temp, line);
		else
			quotes = ft_strdup(line);
		free(temp);
		free(line);
	}
	free(line);
	return (quotes);
}

char	*read_heredoc(char *delimiter)
{
	char	*heredoc;
	char	*line;
	char	*temp;

	heredoc = NULL;
	if (check_delimiter(delimiter))
		return (NULL);
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (heredoc == NULL)
			heredoc = ft_strdup(line);
		else
		{
			temp = ft_strjoin(heredoc, line);
			free(heredoc);
			heredoc = temp;
		}
		free(line);
	}
	free(line);
	return (heredoc);
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
