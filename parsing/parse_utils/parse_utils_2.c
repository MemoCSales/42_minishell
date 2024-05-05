/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_2.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//INSERT SPACES
char	*insert_spaces(char *command)
{
	char	*changed;
	int		i;
	int		j;
printf("\ncommand:%s\n", command);
	i = 0;
	j = 0;
	check_malloc(command);
	changed = malloc(strlen(command) * 5 + 1);
	check_malloc(changed);
	while (command[i])
	{
		changed = insertions(changed, command, &i, &j);
printf("saido do insertions:%s:\n", changed);
		// i++;
	} 
	changed[j] = '\0';
printf("changed:%s:\n", changed);
	return (changed);
}

char	*insertions(char *changed, char *command, int *i, int *j)
{
	printf("command[*i]:%c, command[*i + 1]:%c, command[*i + 2]:%c, command[*i + 3]:%c, command[*i + 4]:%c, command[*i + 5]:%c, command[*i + 6]:%c\n", command[*i], command[(*i) + 1], command[*i + 2], command[*i + 3], command[*i + 4], command[*i + 5], command[*i + 6]);
	if (command[*i] == '>' && command[*i + 1] != '>'
		&& command[*i + 1] != ' ')
		spaces_more_less(changed, j, i, '>');
	else if (command[*i] == '<' && command[*i + 1] != '<'
		&& command[*i + 1] != ' ')
		spaces_more_less(changed, j, i, '<');
	else if (command[*i] == '>' && command[*i + 1] == '>'
		&& command[*i + 2] != ' ')
		spaces_app_hdoc(changed, j, i, ">>");
	else if (command[*i] == '<' && command[*i + 1] == '<'
		&& command[*i + 2] != ' ')
		spaces_app_hdoc(changed, j, i, "<<");
	else
	{
		changed[(*j)++] = command[*i];
        (*i)++;
	}
	changed[*j] = '\0';
	return (changed);
}

void	spaces_more_less(char *changed, int *j, int *i, char symbol)
{
	printf("< or >");
	changed[(*j)++] = ' ';
	changed[(*j)++] = symbol;
	changed[(*j)++] = ' ';
	(*i)++;
}

void	spaces_app_hdoc(char *changed, int *j, int *i, char *symbol)
{
	printf("changed:%s, int j:%d, int i:%d, symbol:\"%s\"\n", changed, *j, *i, symbol);
	// exit(0);
	if (ft_strcmp(symbol, ">>") == 0)
	// if (ft_strcmp(symbol, ">>"))
	{
		printf(">>>>>>>>\n");
		changed[(*j)++] = ' ';
		changed[(*j)++] = '>';
		changed[(*j)++] = '>';
		changed[(*j)++] = ' ';
	// printf("changed2:%s, int j:%d, int i:%d, symbol:%s\n", changed, *j, *i, symbol);
		(*i)++;
	}
	else if (ft_strcmp(symbol, "<<") == 0)
	{
		printf("<<<<<<<<\n");
		changed[(*j)++] = ' ';
		changed[(*j)++] = '<';
		changed[(*j)++] = '<';
		changed[(*j)++] = ' ';
	// printf("changed3:%s, int j:%d, int i:%d, symbol:%s\n", changed, *j, *i, symbol);
	// printf("OLHAAA:%c%c%c%c:\n", changed[(*j)--], changed[(*j)--], changed[(*j)--], changed[(*j)--]);
		(*j)--;
		(*j)--;
		(*j)--;
		// (*j)--;
		// (*i)++;
	}
	else
	{
		printf("outro");
		;
	}
	// (*i)++;
}

//ANTIGAS

// char	*insert_spaces(char *command)// adds spaces around the '>' character
// {
// 	char	*changed;
// 	int		i;
// 	int		j;
// 	int		in_string;// keep track of whether we're inside a string
// 	i = 0;
// 	j = 0;
// 	in_string = 0;
// 	if (!command)
// 	{
// 		ft_putstr_fd("Error: No command specified\n", 2);
// 		exit (1);
// 	}
// 	changed = malloc(strlen(command) * 5 + 1);// for the preprocessed command
// 	if (!changed)
// 	{
// 		ft_putstr_fd("Error: malloc failed\n", 2);
// 		exit (1);
// 	}
// 	while (command[i] != '\0')
// 	{
// 		if (command[i] == '"')
// 		{
// 			in_string = !in_string;// Toggle the in_string variable
// 		}
// 		if (!in_string && command[i] == '>'
// 			&& command[i + 1] != ' ' && command[i + 1] != '>')
// 		{
// // printf("OK0>>\n");
// 			changed[j++] = ' ';
// 			changed[j++] = '>';
// 			changed[j++] = ' ';
// 		}
// 		else if (!in_string && command[i] == '<'
// 			&& command[i + 1] != ' ' && command[i + 1] != '<')
// 		{
// // printf("OK1>>\n");
// 			changed[j++] = ' ';
// 			changed[j++] = '<';
// 			changed[j++] = ' ';
// 		}
// 		else if (!in_string && command[i] == '>'
// 			&& command[i + 1] == '>' && command[i + 2] != ' ')
// 		{
// // printf("OK2>>\n");
// 			changed[j++] = ' ';
// 			changed[j++] = '>';
// 			changed[j++] = '>';
// 			changed[j++] = ' ';
// 			i++;
// 		}
// 		else if (!in_string && command[i] == '<'
// 			&& command[i + 1] == '<' && command[i + 2] != ' ')
// 		{
// // printf("OK3>>\n");
// 			changed[j++] = ' ';
// 			changed[j++] = '<';
// 			changed[j++] = '<';
// 			changed[j++] = ' ';
// 			i++;
// 		}
// 		else
// 		{
// 			changed[j++] = command[i];
// 		}
// 		i++;
// 	}
// 	changed[j] = '\0';// Null-terminate the preprocessed command
// // printf("changed: %s\n", changed);
// // exit(0);
// 	return (changed);
// }

// while (command[i])
// {
//if (command[i] == '>' && command[i + 1] != ' ' && command[i + 1] != '>')
//	spaces_more_less(changed, &j, &i, '>');
//else if (command[i] == '<' && command[i + 1] != ' ' && command[i + 1] != '<')
//	spaces_more_less(changed, &j, &i, '<');
//else if (command[i] == '>' && command[i + 1] == '>' && command[i + 2] != ' ')
//	spaces_append_heredoc(changed, &j, &i, '>', '>');
//else if (command[i] == '<' && command[i + 1] == '<' && command[i + 2] != ' ')
//	spaces_append_heredoc(changed, &j, &i, '<', '<');
//else changed[j++] = command[i];
//i++;
// }




// //INSERT SPACES
// char	*insert_spaces(char *command)
// {
// 	char	*changed;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	check_malloc(command);
// 	changed = malloc(strlen(command) * 5 + 1);
// 	check_malloc(changed);
// 	while (command[i])
// 	{
// 		changed = insertions(changed, command, i, j);
// 		i++;
// 	} 
// 	changed = insertions(changed, command, i, j);
// 	changed[j] = '\0';
// 	return (changed);
// }

// char	*insertions(char *changed, char *command, int i, int j)
// {
// 	if (command[i] == '>' && command[i + 1] != ' '
// 		&& command[i + 1] != '>')
// 		spaces_more_less(changed, &j, &i, '>');
// 	else if (command[i] == '<' && command[i + 1] != ' '
// 		&& command[i + 1] != '<')
// 		spaces_more_less(changed, &j, &i, '<');
// 	else if (command[i] == '>' && command[i + 1] == '>'
// 		&& command[i + 2] != ' ')
// 		spaces_app_hdoc(changed, &j, &i, ">>");
// 	else if (command[i] == '<' && command[i + 1] == '<'
// 		&& command[i + 2] != ' ')
// 		spaces_app_hdoc(changed, &j, &i, "<<");
// 	else
// 		changed[j++] = command[i];
// 	i++;
// 	changed[j] = '\0';
// 	return (changed);
// }