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

void	remove_quotes(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	ft_memmove(arg, arg + 1, len - 1);
	arg[len - 1] = '\0';
}

void	clean_quotes(char **args)
{
	int	count;

	count = 0;
	if (args[0])
	{
		count = count_elements(args);
		if ((count == 1 && !args[1]) || (args[1] && ((args[1][0] == '\"'
					&& args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"')
			|| (args[1][0] == '\'' && args[count - 1]
			[ft_strlen(args[count - 1]) - 1] == '\''))))
		{
			if (args[0][0] == '\"' || args[0][0] == '\'')
			{
				remove_quotes(args[0]);
			}
			if (args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"' ||
			args[count - 1][ft_strlen(args[count - 1]) - 1] == '\'')
			{
				args[count - 1][ft_strlen(args[count - 1]) - 1] = '\0';
			}
		}
	}
}

void	insert_spaces_in_command(char *command, char *changed, int *i, int *j)
{
	int	in_string;

	in_string = 0;
	if (command[*i] == '"')
		in_string = !in_string;
	if (!in_string && (command[*i] == '>' || command[*i] == '<')
		&& command[*i + 1] != ' ' && command[*i + 1] != command[*i])
	{
		changed[(*j)++] = ' ';
		changed[(*j)++] = command[*i];
		changed[(*j)++] = ' ';
	}
	else if (!in_string && command[*i] == command[*i + 1]
		&& command[*i + 2] != ' ')
	{
		changed[(*j)++] = ' ';
		changed[(*j)++] = command[*i];
		changed[(*j)++] = command[*i];
		(*i)++;
		changed[(*j)++] = ' ';
	}
	else
		changed[(*j)++] = command[*i];
	(*i)++;
}

void	process_command(char *command, char *changed)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i])
	{
		insert_spaces_in_command(command, changed, &i, &j);
	}
	changed[j] = '\0';
}

char	*insert_spaces(char *command)
{
	char	*changed;

	if (!command)
	{
		ft_putstr_fd("Error: No command specified\n", 2);
		exit (1);
	}
	changed = malloc(strlen(command) * 5 + 1);
	check_malloc(changed);
	process_command(command, changed);
	return (changed);
}
