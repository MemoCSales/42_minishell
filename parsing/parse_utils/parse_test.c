/* ************************************************************************** */
/*                                                                            */
/*   parse_test.c               ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	append_var_value(char **prepared, int *j, char *var_value)
// {
// 	int		var_value_len;
// 	int		prepared_len;
// 	char	*new_prepared;

// 	var_value_len = strlen(var_value);
// 	prepared_len = strlen(*prepared);
// 	if (prepared_len + var_value_len >= *j)
// 	{
// 		new_prepared = malloc(prepared_len + var_value_len + 1);
// 		check_malloc(new_prepared);
// 		ft_memcpy(new_prepared, *prepared, prepared_len);
// 		new_prepared[prepared_len] = '\0';
// 		free(*prepared);
// 		*prepared = new_prepared;
// 		*j = prepared_len;
// 	}
// 	while (*var_value)
// 	{
// 		(*prepared)[(*j)++] = *var_value;
// 		var_value++;
// 	}
// 	(*prepared)[*j] = '\0';
// }

// void	handle_variables(char *line, char *prepared, int *i, int *j)
// {
// 	char	var_name[1024];
// 	char	*var_value;
// 	int		k;

// 	var_value = NULL;
// 	k = 0;
// 	if (line[*i] == '$')
// 	{
// 		(*i)++;
// 		while (line[*i] != '\0' && (isalnum(line[*i]) || line[*i] == '_'))
// 		{
// 			var_name[k++] = line[(*i)++];
// 		}
// 		var_name[k] = '\0';
// 		var_value = getenv(var_name);
// 		if (var_value)
// 		{
// 			append_var_value(prepared, j, var_value);
// 		}
// 	}
// }

// void	handle_quotes(char *line, int *i, int *in_quotes)
// {
// 	if ((line[*i] == '\'' || line[*i] == '\"') && !is_escaped(line, *i))
// 	{
// 		if (*in_quotes == line[*i])
// 		{
// 			*in_quotes = 0;
// 		}
// 		else
// 		{
// 			*in_quotes = line[*i];
// 		}
// 		(*i)++;
// 	}
// }

// void	handle_others(char *line, char *prepared, int *i, int *j)
// {
// 	if (line[*i] != '\0')
// 	{
// 		(*prepared)[*j] = line[*i];
// 		(*j)++;
// 		(*i)++;
// 	}
// }

// void	handle_input(char *line, char *prepared)
// 	{
// 	int	i;
// 	int	j;
// 	int	in_quotes;

// 	i = 0;
// 	j = 0;
// 	in_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		handle_quotes(line, &i, &in_quotes);
// 		if (in_quotes != '\'')
// 		{
// 			handle_variables(line, prepared, &i, &j);
// 		}
// 		handle_others(line, prepared, &i, &j);
// 	}
// 	prepared[j] = '\0';
// }

// char	*prepare_line(char *line)
// {
// 	char	*prepared;

// 	prepared = malloc(strlen(line) * 2 + 1);
// 	check_malloc(prepared);
// 	handle_input(line, prepared);
// 	return (prepared);
// }
// void	check_malloc(void *ptr)
// {
// 	if (!ptr)
// 	{
// 		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
// 		exit(EXIT_FAILURE);
// 	}
// }
