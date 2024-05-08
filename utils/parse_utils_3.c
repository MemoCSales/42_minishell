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

int		is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char *prepared_input(char *line)
{
	char	*prepared;
	int		i;
	int		j;
	int		in_single_quotes;
	int		in_double_quotes;
	char	*var_name;
	char 	*var_value;
	int		x; // DEBUG
	
	x = 0; // DEBUG
	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	var_name = malloc(256); // Assuming maximum variable name length is 256

	prepared = malloc(ft_strlen(line) + 1);
	check_malloc(prepared);

if (x)
		printf("LINE BEFORE: %s\n", line);
	
	while (line[i] != '\0')
	{
		//INSIDE SINGLE QUOTES
		if ((line[i] == '\'') && !in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			prepared[j] = line[i];
			if (x)
				printf("INSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n", line[i], in_single_quotes);
			j++;
			i++;
			continue;
		}

//OUTSIDE SINGLE QUOTES
		if ((line[i] == '\'') && in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			prepared[j] = line[i];
			if (x)
				printf("OUTSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n", line[i], in_single_quotes);
			j++;
			i++;
			continue;
		}

//INSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && !in_double_quotes)
		{
			in_double_quotes = !in_double_quotes;
			prepared[j] = line[i];
			if (x)
				printf("INSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n", line[i], in_double_quotes);
			j++;
			i++;
			continue;
		}

//OUTSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
		{
			in_double_quotes = !in_double_quotes;
			prepared[j] = line[i];
			if (x)
				printf("OUTSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n", line[i], in_double_quotes);
			j++;
			i++;
			continue;
		}

		if (line[i] == '\"')
		{
			if (line[i-1] == '\\')
			{
				if (x)
					printf("DOUBLE QUOTES WITH \\ BEFORE\n");
				strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
				i++;
			}
			continue ;
		}

		if (is_whitespace(line[i]) && !(in_single_quotes || in_double_quotes))
		{
			if (x)
				printf("WHITESPACE AND OUTSIDE QUOTES\n");
			prepared[j] = line[i];
			i++;
			j++;
			continue ;
		}

		if ((line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == '\\')) &&
			(in_double_quotes) && (!in_single_quotes))
			{
				if (x)
					printf("ESCAPED CHARACTER INSIDE DOUBLE QUOTES AND OUTSIDE SINGLE QUOTES\n");
			prepared[j] = line[i+1];
			i += 2;
			j++;
			continue;
		}

		if ((line[i] == '$' && !in_single_quotes) && (line[i-1] != '\\'))
		{
			if (x)
				printf("DOLLAR SIGN OUTSIDE SINGLE QUOTES AND BEFORE NOT \\\n");

			if (var_name == NULL)
			{
				fprintf(stderr, "Memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
			int k = 0;
			i++; // Skip the '$'
			while (line[i] != '\0' && !is_whitespace(line[i]) && line[i] != '\'' && line[i] != '\"') {
				var_name[k] = line[i];
				i++;
				k++;
			}
			var_name[k] = '\0';
			var_value = getenv(var_name);
			// char *var_value = getenv(var_name);
			if (var_value != NULL)
			{
				// Replace the variable with its value
				int len = strlen(var_value);
				strncpy(&prepared[j], var_value, len);
				j += len;
			}
			free(var_name);
			continue 	;
		}

		else if (((line[i] == '$' && !in_single_quotes) && (line[i-1] == '\\')) ||
				((line[i] == '$' && in_single_quotes) && (line[i-1] == '\\') && in_double_quotes))
		{
			if (x)
				printf("SE DOLLAR SIGN E FORA DE SINGLE QUOTES E ANTERIOR \\, OU DOLLAR SIGN E DENTRO SINGLE QUOTES E ANTERIOR \\ E DENTRO DOUBLE QUOTES\n");
			strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
			i++;
		}

		else if ((line[i] == '$' && in_single_quotes))
		{
			if (x)
				printf("DOLLAR SIGN INSIDE SINGLE QUOTES\n");
			prepared[j] = line[i];
			i++;
			j++;
			continue;
		}

		prepared[j] = line[i];
		i++;
		j++;
	}
	prepared[j] = '\0';

if (x)
		printf("LINE AFTER:  %s\n", prepared);
// exit(0);
	return (prepared);
}