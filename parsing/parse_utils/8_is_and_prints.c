/* ************************************************************************** */
/*                                                                            */
/*   8_is_and_prints.c          ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
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
int	is_char_in_quotes(char *line, int index)
{
    int		status;
    char    *substring;

    substring = malloc((index + 2) * sizeof(char));
    strncpy(substring, line, index + 1);
    substring[index + 1] = '\0';
// printf("substring up to index + 1: %s\n", substring); // Debug print
    status = in_quotes(substring);
// printf("status: %d\n", status); // Debug print
    free(substring);
    return (status);
}
// int	is_char_in_quotes(char *line, int index)
// {
//     char	temp;
//     int		status;

//     temp = line[index + 1];
//     line[index + 1] = '\0';
//     printf("line up to index + 1: %s\n", line); // Debug print
//     status = in_quotes(line);
//     printf("status: %d\n", status); // Debug print
//     line[index + 1] = temp;
//     return (status);
// }

void	print_args(char **args)
{
	int	k;

	k = 0;
	if (!args)
		printf("Argument NULL%d: %s\n", k, args[k]);
	else
	{
		while (args[k] != NULL)
		{
			printf("t_main.args[%d]: %s\n", k, args[k]);
			k++;
		}
	}
}

void	print_struct(t_main *main_var, int i)
{
	if (main_var == NULL)
	{
		ft_putstr_fd("Error: main_var is NULL\n\n", STDERR_FILENO);
		return ;
	}
	printf("\nt_main[%d].cmd: %s\n", i, main_var[i].cmd);
	printf("t_main[%d].flags: %s\n", i, main_var[i].flags);
	print_args(main_var[i].args);
	printf("t_main[%d].input_file: %s\n", i, main_var[i].input_file);
	printf("t_main[%d].output_file: %s\n", i, main_var[i].output_file);
	printf("t_main[%d].heredoc: %s\n", i, main_var[i].heredoc);
	printf("t_main[%d].extra: %s\n", i, main_var[i].extra);
	printf("t_main[%d].fd[0]: %d\n", i, main_var[i].fd[0]);
	printf("t_main[%d].fd[1]: %d\n\n", i, main_var[i].fd[1]);
}

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

// void	copy_increment(char *prepared, const char *line, int *i, int *j)
// {
// 	prepared[*j] = line[*i];
// 	(*i)++;
// 	(*j)++;
// }
