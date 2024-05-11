/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_3.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(char *line, int *i, int *in_quotes)
{
	if ((line[*i] == '\'' || line[*i] == '\"') && !is_escaped(line, *i))
	{
		if (*in_quotes == line[*i])
		{
			*in_quotes = 0;
		}
		else
		{
			*in_quotes = line[*i];
		}
		(*i)++;
	}
}

void	handle_variables(char *line, char *prepared, int *i, int *j)
{
	char	var_name[256];

	if (line[*i] == '$' && (*i == 0 || line[*i - 1] != '\\'))
	{
		(*i)++;
		get_var_name(line, i, var_name);
		replace_var_value(var_name, prepared, j);
	}
}

void	handle_others(char *line, char *prepared, int *i, int *j)
{
	if (line[*i] != '\0')
	{
		prepared[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
}

void	handle_input(char *line, char *prepared)
	{
	int	i;
	int	j;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (line[i] != '\0')
	{
		handle_quotes(line, &i, &in_quotes);
		if (in_quotes != '\'')
		{
			handle_variables(line, prepared, &i, &j);
		}
		handle_others(line, prepared, &i, &j);
	}
	prepared[j] = '\0';
}

char	*prepare_line(char *line)
{
	char	*prepared;

	prepared = malloc(strlen(line) + 1);
	check_malloc(prepared);
	handle_input(line, prepared);
	return (prepared);
}
