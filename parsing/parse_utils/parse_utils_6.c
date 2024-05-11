/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_6.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_delimiter(char *delimiter)
{
	if (!delimiter)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

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

t_main	*initialize_main(t_main *main_var, int num_commands)
{
	int	i;

	i = 0;
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	check_malloc(main_var);
	while (i < num_commands)
	{
		main_var->cmd = NULL;
		main_var->flags = NULL;
		main_var->args = NULL;
		main_var->input_file = NULL;
		main_var->output_file = NULL;
		main_var->heredoc = NULL;
		main_var->extra = NULL;
		main_var->fd[0] = 0;
		main_var->fd[1] = 0;
		i++;
	}
	return (main_var);
}
