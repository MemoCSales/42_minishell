/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_9.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 20:59:34 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*handling(char *command)
// {
// 	char	*processed_command;
// 	int		i;

// 	processed_command = malloc(strlen(command) + 1);
// 	check_malloc(processed_command);
// 	i = 0;
// 	processed_command = pre_handle_quotes(command);
// 	processed_command = pre_handle_escaped_quotes(processed_command);
// 	return (processed_command);
// }

// char	*pre_handle_quotes(char *command)
// {
// 	char	*processed_command;
// 	int		i;
// 	int		j;
// 	int		single_quote_open;
// 	int		double_quote_open;

// 	i = 0;
// 	j = 0;
// 	single_quote_open = 0;
// 	double_quote_open = 0;
// 	processed_command = malloc(strlen(command) + 1);
// 	while (command[i])
// 	{
// 		if (command[i] == '\'' && !double_quote_open)
// 			single_quote_open = !single_quote_open;
// 		else if (command[i] == '\"' && !single_quote_open)
// 			double_quote_open = !double_quote_open;
// 		if (!(single_quote_open && command[i] == '\"')
// 			&& !(double_quote_open && command[i] == '\''))
// 			processed_command[j++] = command[i];
// 		i++;
// 	}
// 	processed_command[j] = '\0';
// 	return (processed_command);
// }

// // char	*pre_handle_escaped_quotes(char *command)
// // {
// // 	char	*processed_command;
// // 	int		j;
// // 	int		i;

// // 	processed_command = malloc(strlen(command) + 1);
// // 	check_malloc(processed_command);
// // 	i = 0;
// // 	j = 0;
// // 	while (command[i] != '\0')
// // 	{
// // 		if (command[i] == '\\'
// // 			&& (command[i + 1] == '"'
// // 				|| command[i + 1] == '\''))
// // 		{
// // 			processed_command[j++] = command[i + 1];
// // 			i++;
// // 		}
// // 		else
// // 			processed_command[j++] = command[i];
// // 		i++;
// // 	}
// // 	processed_command[j] = '\0';
// // 	return (processed_command);
// // }
