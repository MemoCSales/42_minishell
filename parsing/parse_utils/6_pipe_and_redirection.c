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
// printf("*line: %s\n", line);
	quotes = NULL;
	if (check_delimiter(delimiter))
		return (NULL);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		new_line = get_next_line(0);
// printf("new_line: %s\n", new_line);
		temp = ft_strdup(line);
// printf("tempstrdup: %s\n", temp);
		temp = ft_strjoin(new_line, "\n");
// printf("tempstrjoin: %s\n", temp);
		temp = quotes;
// printf("tempquotes: %s\n", temp);
		if (quotes)
		{
			quotes = ft_strjoin(temp, new_line);
// printf("quotesif: %s\n", quotes);
		}
		else
		{
			quotes = ft_strdup(new_line);
// printf("quoteselse: %s\n", quotes);
		}
		free(temp);
		free(new_line);
		if (!new_line || !quotes
			|| !ft_strncmp(new_line, delimiter, ft_strlen(delimiter)))
			break ;
	}
// printf("quotesfinal: %s\n", quotes);
	return (quotes);
}

char	*check_closed_quotes(char *line)
{
	int		single_quote_count;
	int		double_quote_count;
	char	*ptr;

	single_quote_count = 0;
	double_quote_count = 0;
	ptr = line;
	while (*ptr != '\0')
	{
		if (*ptr == '\'')
			single_quote_count++;
		if (*ptr == '\"')
			double_quote_count++;
		ptr++;
	}
	if (single_quote_count % 2 != 0)
	{
		printf("minishell: unclosed single quote\n");
		line = ft_strdup("\'");
		// line = ft_strjoin(line, read_quotes("\'", line));
	}
	else if (double_quote_count % 2 != 0)
	{
		printf("minishell: unclosed double quote\n");
		line = ft_strdup("\"");
		// line = ft_strjoin(line, read_quotes("\"", line));
	}
// printf("line: %s\n", line);
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

// char	*read_quotes(char *delimiter)
// {
//     char	*quotes;
//     char	*line;
//     char	*temp;

//     quotes = NULL;
//     if (check_delimiter(delimiter))
//         return (NULL);
//     while (1)
//     {
//         ft_putstr_fd("> ", 1);
//         line = get_next_line(0);
//         temp = ft_strjoin(line, "\n");
// Join the newline character with line
//         free(line); // Free the old line
//         line = temp;
// Update line to the new string with the newline character
//         if (quotes)
//         {
//             temp = quotes; // Store the old quotes
//             quotes = ft_strjoin(temp, line);
// Join the updated line with quotes
//             free(temp); // Free the old quotes
//         }
//         else
//             quotes = ft_strdup(line);
//         if (!line || !quotes
// || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
//         {
//             free(line); // Free line only once, after it's no longer needed
//             break ;
//         }
//     }
// printf("quotes: %s\n", quotes);
//     return (quotes);
// }