/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_4.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int in_quotes(char *line)
{
	int i;
	int in_single_quotes;
	int in_double_quotes;
	int result = 0;
	
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	
	while (line[i] != '\0') // WHILE NOT THE END OF THE STRING
	{
		// INSIDE SINGLE QUOTES
		if ((line[i] == '\'') && !in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			if (DEBUG)
				// printf("INSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
			i++;
			continue;
		}
		
		// OUTSIDE SINGLE QUOTES
		if ((line[i] == '\'') && in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			if (DEBUG)
				// printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
			i++;
			continue;
		}
		
		// INSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && !in_double_quotes)
		{
			in_double_quotes = !in_double_quotes;
			if (DEBUG)
				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
			i++;
			continue;
		}
		
		// OUTSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
		{
			in_double_quotes = !in_double_quotes;
			if (DEBUG)
				// printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
			i++;
			continue;
		}
		
		i++;
	}
	
	if (in_single_quotes)
		result = 1;
	else if (in_double_quotes)
		result = 2;
	
	return result;
}

// int		in_quotes(char *line)
// {
// 	int	i;
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
	
// 	while (line[i] != '\0') //WHILE NOT THE END OF THE STRING
// 	{
// //INSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && !in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 				printf("INSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //INSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && !in_double_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}
// 	}
	
// 	if (in_single_quotes || in_double_quotes)
// 		return (1);
// 	return (0);
// }