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
//IN QUOTES ESCAPED
int	in_quotes(char *line)
{
    int	i;
    int	in_single_quotes;
    int	in_double_quotes;
    int	last_non_space;
    int	backslashes;

    i = 0;
    in_single_quotes = 0;
    in_double_quotes = 0;
    last_non_space = -1;
    while (line[i] != '\0')
    {
        if (line[i] != ' ')
            last_non_space = i;
        backslashes = 0;
        while (last_non_space > 0 && line[last_non_space - 1] == '\\') {
            backslashes++;
            last_non_space--;
        }
        if (line[i] == '\'' && (last_non_space == -1 || (last_non_space > 0 && backslashes % 2 == 0)))
            in_single_quotes = !in_single_quotes;
        else if (line[i] == '\"' && (last_non_space == -1 || (last_non_space > 0 && backslashes % 2 == 0)))
            in_double_quotes = !in_double_quotes;
// printf("char: %c, in_single_quotes: %d, in_double_quotes: %d\n", line[i], in_single_quotes, in_double_quotes); // Debug print
        i++;
    }
    if (in_single_quotes)
        return (1);
    else if (in_double_quotes)
        return (2);
    else
        return (0);
}
// int	in_quotes(char *line)
// {
//     int	i;
//     int	in_single_quotes;
//     int	in_double_quotes;
//     int	last_non_space;

//     i = 0;
//     in_single_quotes = 0;
//     in_double_quotes = 0;
//     last_non_space = -1;
//     while (line[i] != '\0')
//     {
//         if (line[i] != ' ')
//             last_non_space = i;
//         if (line[i] == '\'' && (last_non_space == -1 || (last_non_space > 0 && line[last_non_space - 1] != '\\')))
//             in_single_quotes = !in_single_quotes;
//         else if (line[i] == '\"' && (last_non_space == -1 || (last_non_space > 0 && line[last_non_space - 1] != '\\')))
//             in_double_quotes = !in_double_quotes;
//         printf("char: %c, in_single_quotes: %d, in_double_quotes: %d\n", line[i], in_single_quotes, in_double_quotes); // Debug print
//         i++;
//     }
//     if (in_single_quotes)
//         return (1);
//     else if (in_double_quotes)
//         return (2);
//     else
//         return (0);
// }
// 0: no quotes, 1: single, 2: double, -1: error - check for unescaped quotes
// int	in_quotes(char *line)
// {
// 	int	i;
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\'')
// 			in_single_quotes = !in_single_quotes;
// 		else if (line[i] == '\"' && (!in_double_quotes || line[i - 1] != '\\'))
// 			in_double_quotes = !in_double_quotes;
// 		i++;
// 	}
// 	if (in_single_quotes)
// 		return (1);
// 	if (in_double_quotes)
// 		return (2);
// 	if (in_single_quotes || in_double_quotes)
// 		return (-1);
// 	return (0);
// }

void	clean_quotes(char **args) // remove quotes from first and last argument
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

void	remove_double_quotes(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}
