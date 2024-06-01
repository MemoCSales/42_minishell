/* ************************************************************************** */
/*                                                                            */
/*   9_is_and_prints.c          ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
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
	char	*substring;

	substring = malloc((index + 2) * sizeof(char));
	ft_strncpy(substring, line, index + 1);
	substring[index + 1] = '\0';
	status = in_quotes(substring);
	free(substring);
	return (status);
}

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
			printf("t_main.args[%d]: %p - %s\n", k, args[k], args[k]);
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

// //PRINT STRUCT
// 	i = 0;
// 	while (parsed_struct[i].cmd)
// 	{
// 		print_struct(&parsed_struct[i], i);
// 		i++;
// 	}