/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_1.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_elements(char **array)
{
	int	num_elements;

	if (!array)
		return (0);
	num_elements = 0;
	while (array[num_elements] != NULL)
		num_elements++;
	return (num_elements);
}

char	**copy_args(char **args)
{
	char	**copy;
	int		num_args;
	int		i;

	if (!args)
		return (NULL);
	num_args = 0;
	while (args [num_args] != NULL)
		num_args ++;
	copy = malloc ((num_args + 1) * sizeof (char *));
	if (!copy)
	{
		ft_putstr_fd ("Error: Unable to allocate memory\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < num_args)
	{
		copy[i] = ft_strdup (args[i]);
		i++;
	}
	copy[num_args] = NULL;
	return (copy);
}

void	remove_args(char **args, int start_index, int num_args)
{
	int	i;
	int	j;

	i = start_index;
	j = start_index + num_args;
	while (args[j] != NULL)
	{
		args[i] = args[j];
		i++;
		j++;
	}
	while (args[i] != NULL)
	{
		args[i] = NULL;
		i++;
	}
}

void	print_args(char **args)
{
	int	k;

	k = 0;
	printf("\n");
	if (!args)
		printf("Argument NULL%d: %s\n", k, args[k]);
	else
	{
		while (args[k] != NULL)
		{
			printf("Argument %d: %s\n", k, args[k]);
			k++;
		}
	}
	printf("Argument %d (after): %s\n", k, args[k]);
	printf("\n");
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
	printf("t_main[%d].input_file: %s\n", i, main_var[i].input_file);
	printf("t_main[%d].output_file: %s\n", i, main_var[i].output_file);
	printf("t_main[%d].heredoc: %s\n", i, main_var[i].heredoc);
	printf("t_main[%d].extra: %s\n", i, main_var[i].extra);
	printf("t_main[%d].fd[0]: %d\n", i, main_var[i].fd[0]);
	printf("t_main[%d].fd[1]: %d\n\n", i, main_var[i].fd[1]);
}
