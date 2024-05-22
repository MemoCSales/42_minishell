/* ************************************************************************** */
/*                                                                            */
/*   14_insert_spaces.c         ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_spaces_in_command(char *command, char *changed, int *i, int *j)
{
	int	in_string;

	in_string = 0;
	if (command[*i] == '"')
		in_string = !in_string;
	if (!in_string && command[*i] == '<' && command[*i + 1] == '<')
		insert_spaces_and_duplicate_command(changed, j, command, i);
	else if (!in_string && command[*i] == '>' && command[*i + 1] == '>')
		insert_spaces_and_duplicate_command(changed, j, command, i);
	else if (!in_string && (command[*i] == '>' || command[*i] == '<')
		&& command[*i + 1] != command[*i])
	{
		changed[(*j)++] = ' ';
		changed[(*j)++] = command[*i];
		changed[(*j)++] = ' ';
	}
	else if (!in_string && command[*i] == command[*i + 1]
		&& command[*i + 2] != ' ' && command[*i] == '>'
		&& command[*i] == '<')
		insert_spaces_and_duplicate_command(changed, j, command, i);
	else
		changed[(*j)++] = command[*i];
	(*i)++;
}

void	insert_spaces_and_duplicate_command(char *changed, \
		int *j, char *command, int *i)
{
	changed[(*j)++] = ' ';
	changed[(*j)++] = command[*i];
	changed[(*j)++] = command[*i];
	(*i)++;
	changed[(*j)++] = ' ';
}
//ANTIGA SE DER RUIM
// void	insert_spaces_in_command(char *command, char *changed, int *i, int *j)
// {
// 	int	in_string;

// 	in_string = 0;
// 	if (command[*i] == '"')
// 		in_string = !in_string;
// 	if (!in_string && command[*i] == '<' && command[*i + 1] == '<')
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = command[*i];
// 		(*i)++;
// 		changed[(*j)++] = ' ';
// 	}
// 	else if (!in_string && command[*i] == '>' && command[*i + 1] == '>')
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = command[*i];
// 		(*i)++;
// 		changed[(*j)++] = ' ';
// 	}
// 	else if (!in_string && (command[*i] == '>' || command[*i] == '<')
// 		&& command[*i + 1] != command[*i])
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = ' ';
// 	}
// 	else if (!in_string && command[*i] == command[*i + 1]
// 		&& command[*i + 2] != ' ' && command[*i] == '>'
// 		&& command[*i] == '<')
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = command[*i];
// 		(*i)++;
// 		changed[(*j)++] = ' ';
// 	}
// 	else
// 		changed[(*j)++] = command[*i];
// 	(*i)++;
// }