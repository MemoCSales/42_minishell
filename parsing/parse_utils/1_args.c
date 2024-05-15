/* ************************************************************************** */
/*                                                                            */
/*   1_args.c                   ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	remove_args_first_last_quotes(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	ft_memmove(arg, arg + 1, len - 1);
	arg[len - 1] = '\0';
}
