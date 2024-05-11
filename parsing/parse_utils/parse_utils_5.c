/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_5.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_quotes(char **args)
{
	int		len;
	int		k;

	k = 0;
//IF IT HAS AT LEAST ONE ARGUMENT, AFTER THE SPLIT
	if (args[0])
	{
		if (DEBUG)
		{
			printf ("PRINT FIRST AND LAST CHARACTERS\n");
			printf ("args[0][0]: %c\n", args[0][0]);
			printf ("args[LAST]: %c\n\n", args[count_elements(args) - 1]
			[strlen(args[count_elements(args) - 1]) - 1]);
		}
//IF JUST ONE ARGUMENT, AND HAVE QUOTES
		if (DEBUG)
			printf ("NUM ARGS: %d\n", count_elements(args));
		if ((count_elements(args) == 1) && !args[1])
		{
			if ((args[0][0] == '\"' && args[count_elements(args) - 1]
				[strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
				(args[0][0] == '\'' && args[count_elements(args) - 1]
				[strlen(args[count_elements(args) - 1]) - 1] == '\''))
			{
				if (DEBUG)
					printf("JUST ONE ARGUMENT AND HAVE QUOTES\n\n");
// SHIFT LEFT INITIAL QUOTE
				if ((args[0][0] == '\"') || (args[0][0] == '\''))
				{
					len = ft_strlen(args[0]);
					while (k < len)
					{
						args[0][k] = args[0][k + 1];
						k ++;
					}
					args[0][len - 1] = '\0';
				}
// TRIM FINAL QUOTE
				if ((args[count_elements(args) - 1][strlen(args[count_elements
								(args) - 1]) - 1] == '\"') ||
						(args[count_elements(args) - 1][strlen(args
						[count_elements(args) - 1]) - 1] == '\''))
				{
					len = strlen(args[count_elements(args) - 1]);
					args[count_elements(args) - 1][len - 1] = '\0';
				}
			}
			if (DEBUG)
			{
				printf("CLEANED QUOTES");
				print_args(args);
			}
		}
// IF MORE THAN ONE ARGUMENT, AND FIRST AND LAST ARGUMENTS HAVE QUOTES
		if (args[1] && ((args[1][0] == '\"' && args[count_elements(args)
					- 1][strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
					(args[1][0] == '\'' && args[count_elements(args) - 1]
					[strlen(args[count_elements(args) - 1]) - 1] == '\'')))
		{
			if (DEBUG)
				printf("FIRST AND LAST ARGUMENTS HAVE QUOTES\n\n");
//ERASE INITIAL QUOTE
			if ((args[1][0] == '\"') || (args[1][0] == '\''))
			{
				len = strlen(args[1]);
				while (k < len)
				{
					args[1][k] = args[1][k + 1];
					k++;
				}
				args[1][len - 1] = '\0';
			}
			if (DEBUG)
			{
				printf("CLEANED INITIAL QUOTE:");
				print_args(args);
			}
//ERASE FINAL QUOTE
			if ((args[count_elements(args) - 1]
					[strlen(args[count_elements(args) - 1]) - 1] == '\"')
				|| (args[count_elements(args) - 1]
					[strlen(args[count_elements(args) - 1]) - 1] == '\''))
			{
				len = strlen(args[count_elements(args) - 1]);
				args[count_elements(args) - 1][len - 1] = '\0';
			}
			if (DEBUG)
			{
				printf("CLEANED FINAL QUOTE:");
				print_args(args);
			}
		}
	}
}

void	get_var_name(char *line, int *i, char *var_name)
{
	int	j;

	j = 0;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		var_name[j++] = line[*i];
		(*i)++;
	}
	var_name[j] = '\0';
}

void	replace_var_value(char *var_name, char *prepared, int *j)
{
	char	*var_value;
	int		k;

	k = 0;
	var_value = getenv(var_name);
	if (var_value != NULL)
	{
		while (var_value[k] != '\0')
		{
			prepared[*j] = var_value[k];
			(*j)++;
			k++;
		}
	}
}

int	is_escaped(char *line, int index)
	{
	int	count;

	count = 0;
	index--;
	while (index >= 0 && line[index] == '\\')
	{
		count++;
		index--;
	}
	return (count % 2 != 0);
}
