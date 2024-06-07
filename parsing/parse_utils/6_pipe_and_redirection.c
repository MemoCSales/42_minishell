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

char	*read_quotes(char *delimiter, char *line)
{
	char	*quotes;
	char	*new_line;
	char	*temp;

	quotes = NULL;
	if (check_delimiter(delimiter))
		return (NULL);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		new_line = get_next_line(0);
		temp = ft_strdup(line);
		temp = ft_strjoin(new_line, "\n");
		temp = quotes;
		if (quotes)
			quotes = ft_strjoin(temp, new_line);
		else
			quotes = ft_strdup(new_line);
		free(temp);
		free(new_line);
		if (!new_line || !quotes
			|| !ft_strncmp(new_line, delimiter, ft_strlen(delimiter)))
			break ;
	}
	return (quotes);
}

char	*check_closed_quotes(char *line)
{
	int		single_quote_count;
	int		double_quote_count;
	char	*ptr;
	int		in_single_quotes;
	int		in_double_quotes;

	single_quote_count = 0;
	double_quote_count = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	ptr = line;
	while (*ptr != '\0')
	{
		if (*ptr == '\'' && !in_double_quotes)
			in_single_quotes = ++single_quote_count % 2;
		if (*ptr == '\"' && !in_single_quotes)
			in_double_quotes = ++double_quote_count % 2;
		ptr++;
	}
	if (in_single_quotes)
		line = ft_strdup("\'");
	else if (in_double_quotes)
		line = ft_strdup("\"");
	return (line);
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
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (ft_strequ(line, delimiter))
			break ;
		if (heredoc == NULL)
			heredoc = ft_strdup(line);
		else
		{
			temp = ft_strjoin(heredoc, line);
			free(heredoc);
			heredoc = ft_strjoin(temp, "\n");
		}
		free(line);
	}
	free(line);
	return (heredoc);
}

// char	*read_heredoc(char *delimiter)
// {
// 	char	*heredoc;
// 	char	*line;
// 	char	*temp;

// 	heredoc = NULL;
// 	if (check_delimiter(delimiter))
// 		return (NULL);
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		line = get_next_line(0);
// 		// if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 		if (ft_strequ(line, delimiter))
// 			break ;
// 		if (heredoc == NULL)
// 			heredoc = ft_strdup(line);
// 		else
// 		{
// 			temp = ft_strjoin(heredoc, line);
// 			free(heredoc);
// 			// heredoc = temp;
// 			heredoc = ft_strjoin(temp, "\n");
// 		}
// 		free(line);
// 	}
// 	free(line);
// 	return (heredoc);
// }

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
		if (check_redir(parsed_struct, args, j))
		{
			redirection(parsed_struct, args, i, j);
			j--;
		}
		j++;
	}
}
