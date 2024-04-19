/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(char **cmds)
{
	int	num_commands;

	num_commands = 0;
	while(cmds[num_commands] != NULL)
		num_commands++;
	return(num_commands);
}

// After calling this function with this input = echo Hello World
// The output is this one
// t_main parsed_commands[] = {
//     {
//         .cmd = "echo",
//			.flags = "-a",
//         .args = {"Hello,", "world!", NULL}
//     },
//     {
//         .cmd = NULL
//     }
// };
// SYNTAX: command [flags] [arguments]

t_main	*parse_line(char *line)
{
	t_main	*parsed_commands;
	char	**args;
	char	**commands;
	int		num_commands;
	int		i;

	commands = ft_split(line, '|');
	num_commands = count_cmds(commands);
	// while (commands[num_commands] != NULL)
	// 	num_commands++;
	parsed_commands = malloc((num_commands + 1) * sizeof(t_main));
	if (!parsed_commands)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < num_commands)
	{
		args = ft_split(commands[i], ' '); // Split the command into arguments
		parsed_commands[i].cmd = args[0];  // The first argument is the command
		if (args[1] && args[1][0] == '-') // Check if the second argument is a flag
		{
			parsed_commands[i].flags = args[1]; // Saving the flags
			parsed_commands[i].args = &args[2]; // The rest are arguments
		}
		else
		{
			parsed_commands[i].flags = NULL;    // No flags
			parsed_commands[i].args = &args[1]; // The rest are arguments
		}
		if (i < num_commands - 1)
		{
			if (pipe(parsed_commands[i].fd) == -1)
			{
				perror("Pipe error");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
	parsed_commands[num_commands].cmd = NULL;
	free(commands);
	return (parsed_commands);
}

// char	**copy_args(char **args)
// {
// 	char	**copy;
// 	int		num_args;
// 	int		i;

// 	num_args = 0;
// 	while(args[num_args] != NULL)
// 		num_args++;
// 	copy = malloc((num_args + 1) * sizeof(char *));
// 	if (!copy)
// 	{
// 		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < num_args)
// 	{
// 		copy[i] = ft_strdup(args[i]);
// 		i++;
// 	}
// 	copy[num_args] = NULL;
// 	return(copy);
// }
