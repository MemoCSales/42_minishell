/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_3.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//EDITORS
void	check_malloc(char *function)
{
	if (!function)
	{
		ft_putstr_fd("Error: No command specified\n", 2);
		exit (1);
	}
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
	printf("SAIU DO REMOVE_ARGS\n");
}
// In this function, you're shifting the elements of the args 
// array to the left by num_args positions starting from start_index.
// However, you're not ensuring that i + num_args is a valid index
// of the args array. If i + num_args is out of bounds of the args array,
// then args[i + num_args] will be accessing memory that it's not supposed to,
// which could be causing the segmentation fault.
// void	remove_args(char **args, int start_index, int num_args)

// {
// 	int	i;

// 	i = start_index;
// 	while (args[i] != NULL)
// 	{
// 		args[i] = args[i + num_args];
// 		i++;
// 	}
// }

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

void	ft_erase_quotes(char *tkn)
{
	int	i;
	int	double_q_flag;
	int	single_q_flag;

	i = 0;
	double_q_flag = 0;
	single_q_flag = 0;
	while (tkn[i])
	{
		if (tkn[i] == '"' && single_q_flag == 0)
		{
			double_q_flag = !double_q_flag;
			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
			continue ;
		}
		else if (tkn[i] == '\'' && double_q_flag == 0)
		{
			single_q_flag = !single_q_flag;
			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
			continue ;
		}
		i++;
	}
}
// char	*ft_quotes (char *string) //this function removes quotes
// from a string, respecting its hierarchy
// {
// 	char	*new_string;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	new_string = malloc (strlen (string) + 1);
// 	if (!new_string)
// 	{
// 		ft_putstr_fd ("Error: Unable to allocate memory\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	while (string[i] != '\0')
// 	{
// 		if (string[i] != '"' && string[i] != '\'')
// 		{
// 			new_string[j] = string[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_string[j] = '\0';
// 	return (new_string);
// }
