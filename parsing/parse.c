/* ************************************************************************** */
/*                                                                            */
/*   parse.c                    ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_main	*parse_line(char *line)
{
	t_main	*parsed_commands;
	char	**args;
	char	**commands;
	int		num_commands;
	// int		num_args;
	int		i;
	int		j;
	// int		temp;
	char	*delimiter;
	char	*heredoc;
	char	*changed;

	heredoc = NULL;
	changed = NULL;
	i = 0;
	// temp = 0;
	commands = ft_split(line, '|');
	num_commands = count_cmds(commands);
	parsed_commands = NULL;
	parsed_commands = initialize_main(parsed_commands, num_commands);
	if (!parsed_commands)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		return (NULL);
	}
	while (i < num_commands) // Loop Geral do parse_line !!!
	{
		changed = insert_spaces(commands[i]);
										// printf("CHANGED:%s\n", changed);
		args = ft_split(changed, ' '); // Split the command into arguments
		// num_args = count_args(args);
		// args = ft_split(commands[i], ' ');
		// Split the command into arguments
		parsed_commands[i].input_file = NULL;
		parsed_commands[i].output_file = NULL;
		j = 0;
// ERASE QUOTES
		while (args[j] != NULL) // Loop through all the arguments,
									// so we can CHECK FOR REDIRECTIONS
		{
		// printf("ERASE QUOTES\n");
			ft_erase_quotes(args[j]);
// ">>" APPEND
			if (ft_strcmp(args[j], ">>") == 0
				&& args[j + 1]) // Check for heredoc
			{
				// printf("ENTROU NO >> APPEND\n");
				parsed_commands[i].output_file = ft_strdup(args[j + 1]);
				parsed_commands[i].heredoc = ft_strdup(args[j]);
				//passing ">>" to heredoc, to signal that it is a append
				remove_args(args, j, 2);
			//PRINT PARSE_COMMANDS
				// printf("\nEND PARSED APPEND\n");
				// printf("i: %d  /  j: %d  /  argv[j]: %s\n", i, j, args[j]);
				// printf("parsed_commands[i].cmd: %s\n", parsed_commands[i].cmd);
				// printf("parsed_commands[i].flags: %s\n",
				// 	parsed_commands[i].flags);
			//PRINT ARGS
			// 	temp = j;
			// 	j = 0;
			// 	while (j <= count_args(parsed_commands[i].args))
			// 	{
			// 		if (parsed_commands[i].args && parsed_commands[i].args[j])
			// 		{
			// 			printf("parsed_commands[i].args[%d]: %s\n", j,
			// 				parsed_commands[i].args[j]);
			// 		}
			// 		else
			// 		{
			// 			printf("parsed_commands[i].args[%d]: NULL\n", j);
			// 		}
			// 		j++;
			// 	}
			// 	j = temp;
			// //end PRINT ARGS
			// 	printf("parsed_commands[i].input_file: %s\n",
			// 		parsed_commands[i].input_file);
			// 	printf("parsed_commands[i].output_file: %s\n",
			// 		parsed_commands[i].output_file);
			// 	printf("parsed_commands[i].heredoc: %s\n",
			// 		parsed_commands[i].heredoc);
			// 	printf("parsed_commands[i].fd[0]: %d\n",
			// 		parsed_commands[i].fd[0]);
			// 	printf("parsed_commands[i].fd[1]: %d\n",
			// 		parsed_commands[i].fd[1]);
			//end PRINT PARSE_COMMANDS
				break ;
			}
// "<<" HEREDOC
			else if (ft_strcmp(args[j], "<<") == 0
				&& args[j + 1]) // Check for heredoc
			{
				// printf ("ENTROU NO << HEREDOC\n");
				delimiter = args[j + 1];
				heredoc = read_heredoc(delimiter);
				parsed_commands[i].heredoc = heredoc;
				remove_args (args, j, 2);
			//PRINT PARSE_COMMANDS
			// 	printf("\nEND PARSED HEREDOC\n");
			// 	printf("i: %d  /  j: %d  /  argv[j]: %s\n", i, j, args[j]);
			// 	printf("parsed_commands[i].cmd: %s\n", parsed_commands[i].cmd);
			// 	printf("parsed_commands[i].flags: %s\n",
			// 		parsed_commands[i].flags);
			// //PRINT ARGS
			// 	temp = j;
			// 	j = 0;
			// 	while (j <= count_args(parsed_commands[i].args))
			// 	{
			// 		if (parsed_commands[i].args && parsed_commands[i].args[j])
			// 		{
			// 			printf("parsed_commands[i].args[%d]: %s\n", j,
			// 				parsed_commands[i].args[j]);
			// 		}
			// 		else
			// 		{
			// 			printf("parsed_commands[i].args[%d]: NULL\n", j);
			// 		}
			// 		j++;
			// 	}
			// 	j = temp;
			//end PRINT ARGS
				// printf("parsed_commands[i].input_file: %s\n",
				// 	parsed_commands[i].input_file);
				// printf("parsed_commands[i].output_file: %s\n",
				// 	parsed_commands[i].output_file);
				// printf("parsed_commands[i].heredoc: %s\n",
				// 	parsed_commands[i].heredoc);
				// printf("parsed_commands[i].fd[0]: %d\n",
				// 	parsed_commands[i].fd[0]);
				// printf("parsed_commands[i].fd[1]: %d\n",
				// 	parsed_commands[i].fd[1]);
			//end PRINT PARSE_COMMANDS
				break ;
			}
// "<" INPUT
			else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
			{
				// printf("\n### (( \"<\" INPUT ))\n\n");
				parsed_commands[i].input_file = ft_strdup(args[j + 1]);
				remove_args(args, j, 2);
				break ;
			}
// ">" OUTPUT
			else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
			{
				// printf("\n### (( \">\" OUTPUT ))\n\n");
				parsed_commands[i].output_file = ft_strdup(args[j + 1]);
				remove_args(args, j, 2);
				break ;
			}
// NO WEIRD STUFF
			else
			{
			// printf("\n\nARG NO WEIRD STUFF: %s\n", args[j]);
			// printf("NO WEIRD STUFF\n");
				j++;
			}
		}
		parsed_commands[i].cmd = args[0];// Assigning command
//#COMECO DA SEGUNDA PARTE
// "-" FLAGS
		if (args[1] && args[1][0] == '-')
		// Check if the second argument is a flag
		{
			// printf("FLAGS\n");
			// printf("args 1: %s\n", args[1]);
			// exit(0);
			parsed_commands[i].flags = args[1];
			// Saving the flags -- ANTES era ft_strdup(args[1])
			// printf("%s\n", parsed_commands[i].flags);
			parsed_commands[i].args = copy_args(&args[2]);
			// The rest are arguments
			// printf("%s\n", parsed_commands[i].flags);
		}
// NO FLAGS
		else
		{
		// printf("NO FLAGS\n");
			parsed_commands[i].flags = NULL; // No flags
			parsed_commands[i].args = copy_args(&args[1]);
			// The rest are arguments
		}
		if (i < num_commands - 1)
		// If we are not at the last command, create a pipe
		{
			if (pipe (parsed_commands[i].fd) == -1) // Create a pipe
			{
				perror ("Pipe error"); // Print error message, in case of error
				exit (EXIT_FAILURE); // Exit the program
			}
// "|" PIPES
		// printf("WITH PIPES\n");
		}
	//PRINT PARSE_COMMANDS
		// printf("\nEND PARSED COMMANDS\n");
		// // printf("i: %d  /  j: %d  /  argv[j]: %s\n", i, j, args[j]);
		// printf("parsed_commands[i].cmd: %s\n", parsed_commands[i].cmd);
		// printf("parsed_commands[i].flags: %s\n", parsed_commands[i].flags);
	//PRINT ARGS
		// temp = j;
		// j = 0;
		// while (j <= count_args(parsed_commands[i].args))
		// {
		// 	if (parsed_commands[i].args && parsed_commands[i].args[j])
		// 	{
		// 		printf("parsed_commands[i].args[%d]: %s\n", j,
		// 			parsed_commands[i].args[j]);
		// 	}
		// 	else
		// 	{
		// 		printf("parsed_commands[i].args[%d]: NULL\n", j);
		// 	}
		// 	j++;
		// }
		// j = temp;
	// //end PRINT ARGS
		// printf("parsed_commands[i].input_file: %s\n",
		// 	parsed_commands[i].input_file);
		// printf("parsed_commands[i].output_file: %s\n",
		// 	parsed_commands[i].output_file);
		// printf("parsed_commands[i].heredoc: %s\n", parsed_commands[i].heredoc);
		// printf("parsed_commands[i].fd[0]: %d\n", parsed_commands[i].fd[0]);
		// printf("parsed_commands[i].fd[1]: %d\n", parsed_commands[i].fd[1]);
	//end PRINT PARSE_COMMANDS
		i++;// Increment the command index, so we can move to the next command
	}
	parsed_commands[num_commands].cmd = NULL;
	// Null-terminate the array of commands
// print_struct(parsed_commands, num_commands); // printing parsing results
	// printf("RETURN\n");
// FREE MEMORY
	// free (commands);
	// printf("FREED COMMANDS\n");
	// free (changed);
	// printf("FREED CHANGED\n");
	// free (args);
	// printf("FREED ARGS\n");
// exit(0);
	return (parsed_commands);
}
// // ψΨψΨψΨψΨψΨψΨψΨψΨψΨ ATE AQUI, TESTANDO ψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨ
// exit(0);
// // ψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨψΨΨψΨψΨψ
