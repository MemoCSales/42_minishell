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

char	*read_quotes(char *delimiter)
{
	char	*quotes;
	char	*line;
	char	*temp;

	quotes = NULL;
	if (DEBUG)
		printf("ENTROU NO READ_QUOTES\n");
	if (!delimiter)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (NULL);
	}
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		if (quotes == NULL)
		{
			quotes = ft_strdup(line);
		}
		else
		{
			temp = malloc(ft_strlen(quotes) + ft_strlen(line) + 1);
			ft_strlcpy(temp, quotes, ft_strlen(quotes) + 1);
			ft_strlcat(temp, line, ft_strlen(quotes) + ft_strlen(line) + 1);
			free(quotes);
			quotes = temp;
		}
		free (line);
	}
	if (DEBUG)
		printf("SAIU DO QUOTES:%s\n", quotes);
	return (quotes);
}

char	*read_heredoc(char *delimiter)
{
	char	*heredoc;
	char	*line;
	char	*temp;

	heredoc = NULL;
	if (!delimiter)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (NULL);
	}
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		if (heredoc == NULL)
		{
			heredoc = ft_strdup(line);
		}
		else
		{
			temp = malloc(ft_strlen(heredoc) + ft_strlen(line) + 1);
			ft_strlcpy(temp, heredoc, ft_strlen(heredoc) + 1);
			ft_strlcat(temp, line, ft_strlen(heredoc) + ft_strlen(line) + 1);
			free(heredoc);
			heredoc = temp;
		}
		free (line);
	}
	return (heredoc);
}

char	*insert_spaces(char *command)
{
	char	*changed;
	int		i;
	int		j;
	int		in_string;

	i = 0;
	j = 0;
	in_string = 0;
	if (!command)
	{
		ft_putstr_fd("Error: No command specified\n", 2);
		exit (1);
	}
	changed = malloc(strlen(command) * 5 + 1);
	if (!changed)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit (1);
	}
	while (command[i] != '\0')
	{
		if (command[i] == '"')
		{
			in_string = !in_string;
		}
		if (!in_string && command[i] == '>'
			&& command[i + 1] != ' ' && command[i + 1] != '>')
		{
			changed[j++] = ' ';
			changed[j++] = '>';
			changed[j++] = ' ';
		}
		else if (!in_string && command[i] == '<'
			&& command[i + 1] != ' ' && command[i + 1] != '<')
		{
			changed[j++] = ' ';
			changed[j++] = '<';
			changed[j++] = ' ';
		}
		else if (!in_string && command[i] == '>'
			&& command[i + 1] == '>' && command[i + 2] != ' ')
		{
			changed[j++] = ' ';
			changed[j++] = '>';
			changed[j++] = '>';
			changed[j++] = ' ';
			i++;
		}
		else if (!in_string && command[i] == '<'
			&& command[i + 1] == '<' && command[i + 2] != ' ')
		{
			changed[j++] = ' ';
			changed[j++] = '<';
			changed[j++] = '<';
			changed[j++] = ' ';
			i++;
		}
		else
		{
			changed[j++] = command[i];
		}
		i++;
	}
	changed[j] = '\0';
	return (changed);
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
