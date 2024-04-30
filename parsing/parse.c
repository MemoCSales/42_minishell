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

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i, j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			break;
		i++;
	}
	if (str[i] == '\0')
		return str;
	new_str = malloc(ft_strlen(str) + 1);
	if(!new_str)
	{
		perror("Error: Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	remove_args(char **args, int start_index, int num_args)
{
	int	i;

	i = start_index;
	while (args[i] != NULL)
	{
		args[i] = args[i + num_args];
		i++;
	}
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
	int		j;

	commands = ft_split(line, '|');
	num_commands = count_cmds(commands);
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
		parsed_commands[i].input_file = NULL;
		parsed_commands[i].output_file = NULL;
		j = 0;
		while (args[j] != NULL)
		{
			args[j] = remove_quotes(args[j]); // fix this
			if (ft_strcmp(args[j], "<") == 0)
			{
				parsed_commands[i].input_file = args[j + 1];
				remove_args(args, j, 2);
			}
			else if (ft_strcmp(args[j], ">") == 0)
			{
				parsed_commands[i].output_file = args[j + 1];
				remove_args(args, j, 2);
			}
			else
				j++;
		}
		parsed_commands[i].cmd = args[0];  // Assigning command
		if (args[1] && args[1][0] == '-') // Check if the second argument is a flag
		{
			parsed_commands[i].flags = args[1]; // Saving the flags
			parsed_commands[i].args = copy_args(&args[2]); // The rest are arguments
		}
		else
		{
			parsed_commands[i].flags = NULL;    // No flags
			parsed_commands[i].args = copy_args(&args[1]); // The rest are arguments
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
	// free(args);
	return (parsed_commands);
}

char	**copy_args(char **args)
{
	char	**copy;
	int		num_args;
	int		i;

	num_args = 0;
	while(args[num_args] != NULL)
		num_args++;
	copy = malloc((num_args + 1) * sizeof(char *));
	if (!copy)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < num_args)
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[num_args] = NULL;
	return(copy);
}
