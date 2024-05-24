/* ************************************************************************** */
/*                                                                            */
/*   4_quotes.c                 ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
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
			*in_quotes = 0;
		else
			*in_quotes = line[*i];
		(*i)++;
	}
}

int	return_quotes(int in_single_quotes, int in_double_quotes)
{
	if (in_single_quotes)
		return (1);
	else if (in_double_quotes)
		return (2);
	else
		return (0);
}

int	in_quotes(char *line)
{
	t_quotes_escaped	q_vars;

	q_vars.i = 0;
	q_vars.in_single_quotes = 0;
	q_vars.in_double_quotes = 0;
	q_vars.last_unspace = -1;
	while (line[q_vars.i] != '\0')
	{
		if (line[q_vars.i] != ' ')
			q_vars.last_unspace = q_vars.i;
		q_vars.bckslash = 0;
		while (q_vars.last_unspace > 0 && line[q_vars.last_unspace - 1] == '\\')
		{
			q_vars.bckslash++;
			q_vars.last_unspace--;
		}
		if (line[q_vars.i] == '\'' && (q_vars.last_unspace == -1
				|| (q_vars.last_unspace >= 0 && q_vars.bckslash % 2 == 0)))
			q_vars.in_single_quotes = !q_vars.in_single_quotes;
		else if (line[q_vars.i] == '\"' && (q_vars.last_unspace == -1
				|| (q_vars.last_unspace >= 0 && q_vars.bckslash % 2 == 0)))
			q_vars.in_double_quotes = !q_vars.in_double_quotes;
		q_vars.i++;
	}
	return (return_quotes(q_vars.in_single_quotes, q_vars.in_double_quotes));
}

//REMOVE QUOTES FROM FIRST AND LAST ARGUMENTS
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
				remove_args_first_last_quotes(args[0]);
			}
			if (args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"' ||
			args[count - 1][ft_strlen(args[count - 1]) - 1] == '\'')
			{
				args[count - 1][ft_strlen(args[count - 1]) - 1] = '\0';
			}
		}
	}
}

void	erase_quotes(char *command)
{
	int	i;
	int	double_q_flag;
	int	single_q_flag;

	i = 0;
	double_q_flag = 0;
	single_q_flag = 0;
	while (command[i])
	{
		if (command[i] == '"' && single_q_flag == 0)
		{
			double_q_flag = !double_q_flag;
			ft_strcpy(&command[i], (const char *)&command[i + 1]);
			continue ;
		}
		else if (command[i] == '\'' && double_q_flag == 0)
		{
			single_q_flag = !single_q_flag;
			ft_strcpy(&command[i], (const char *)&command[i + 1]);
			continue ;
		}
		i++;
	}
}
