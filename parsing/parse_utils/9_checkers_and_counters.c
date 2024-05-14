/* ************************************************************************** */
/*                                                                            */
/*   9_checkers_and_counters.c      ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	check_flags(t_main *command, char **args)
{
	if (args[1] && args[1][0] == '-')
	{
		command->flags = args[1];
		command->args = copy_args(&args[2]);
	}
	else
	{
		command->flags = NULL;
		command->args = copy_args(&args[1]);
	}
}

int	check_delimiter(char *delimiter)
{
	if (!delimiter)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

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

void	print_ph_strings(char ***ph_strings)
{
	int	i;

	i = 0;
	while ((*ph_strings)[i] != NULL)
	{
		printf("ph_strings[%d]: %s\n", i, (*ph_strings)[i]);
		i++;
	}
}
