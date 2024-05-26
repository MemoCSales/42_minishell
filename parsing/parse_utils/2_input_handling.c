/* ************************************************************************** */
/*                                                                            */
/*   2_input_handling.c         ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_unq_dolar	*process_dollar_unquoted(t_unq_dolar \
	*un_dollar_vars, char *str)
{
	t_unq_dolar	*p_unq_dollar;

	p_unq_dollar = un_dollar_vars;
	p_unq_dollar->start = p_unq_dollar->i;
	while (str[p_unq_dollar->i] != ' ' && str[p_unq_dollar->i] != '\0')
		p_unq_dollar->i++;
	p_unq_dollar->len = p_unq_dollar->i - p_unq_dollar->start;
	ft_strncpy(&p_unq_dollar->result[p_unq_dollar->j], "\"", 1);
	ft_strncpy(&p_unq_dollar->result[p_unq_dollar->j + 1], \
		&str[p_unq_dollar->start], p_unq_dollar->len);
	ft_strncpy(&p_unq_dollar->result[p_unq_dollar->j \
		+ p_unq_dollar->len + 1], "\"", 1);
	p_unq_dollar->j += p_unq_dollar->len + 2;
	return (p_unq_dollar);
}

char	*change_unquoted_dollar_signs(char *str)
{
	t_unq_dolar	unq_dollar;

	unq_dollar.result = malloc(strlen(str) * 2);
	unq_dollar.i = 0;
	unq_dollar.j = 0;
	unq_dollar.in_double_quotes = 0;
	unq_dollar.in_single_quotes = 0;
	while (str[unq_dollar.i] != '\0')
	{
		if (str[unq_dollar.i] == '"')
			unq_dollar.in_double_quotes = !unq_dollar.in_double_quotes;
		if (str[unq_dollar.i] == '\'')
			unq_dollar.in_single_quotes = !unq_dollar.in_single_quotes;
		if (!unq_dollar.in_double_quotes
			&& !unq_dollar.in_single_quotes && str[unq_dollar.i] == '$'
			&& str[unq_dollar.i - 1] != '\\')
			unq_dollar = *process_dollar_unquoted(&unq_dollar, str);
		else
			unq_dollar.result[unq_dollar.j++] = str[unq_dollar.i++];
	}
	unq_dollar.result[unq_dollar.j] = '\0';
	return (unq_dollar.result);
}

char	*prepare_line(char *line, char ***ph_strings, t_env *env_var)
{
	char	*prepared;

	prepared = malloc(strlen(line) + 8192);
	check_malloc(prepared);
	prepared = check_closed_quotes(line);
	if ((ft_strequ(prepared, "\'") || ft_strequ(prepared, "\"")))
	{
		printf("Error: Unclosed quotes (%c)\n", prepared[0]);
		free(prepared);
		prepared = ft_strdup("\0");
		check_malloc(prepared);
		return (prepared);
	}
	prepared = handle_variables(line, env_var);
	*ph_strings = malloc(sizeof(char **) * (strlen(line) + 8192));
	check_malloc(ph_strings);
	placeholder(prepared, ph_strings);
	return (prepared);
}

int	file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		return (0);
	}
	else
	{
		close(fd);
		return (1);
	}
}

int	redir_no_arg(char **args, int j)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(args[j], "<") == 0)
	{
		if (file_exists(args[j + 1]) == 1)
			return (0);
		else
			printf("Error: No such file or directory: %s\n", args[j + 1]);
	}
	else if ((ft_strcmp(args[j], ">") == 0) || ft_strcmp(args[j], ">>") == 0)
	{
		if (file_exists(args[j + 1]) == 1)
			return (0);
		else
		{
			fd = open(args[j + 1], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0644);
			if (fd < 0)
				error_messages("ERROR_OPEN_FILE");
			close(fd);
		}
	}
	return (0);
}
