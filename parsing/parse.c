/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 05:25:58 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_main	*parse_line(char *line)
{
	t_main	*parsed_struct;
	char	**args;
	char	**commands;
	int		num_commands;

	int		i;
	int		j;
	int		f;
	int		x = 0; //DEBUG

	i = 0;
	f = 1;
// SPLIT LINE INTO COMMANDS
	commands = ft_split(line, '|');
	num_commands = count_cmds(commands);
	if (x)
		printf("\nNUM COMMANDS: %d\n\n", num_commands);

// INITIALIZE AND CHECK STRUCT
	parsed_struct = NULL;
	parsed_struct = initialize_main(parsed_struct, num_commands);
	// check_malloc(parsed_struct); //SE JA CHECA NO INITIALIZE_MAIN, ACHO Q NAO PRECISA
	
// LOOP THE COMMANDS
	while (i < num_commands)
	{

// CHANGE ARGUMENTS TO HAVE SPACES
		commands[i] = insert_spaces(commands[i]);
		// printf("CHANGED:%s\n", commands[i]);

// SPLIT COMMAND INTO ARGUMENTS
		args = ft_split(commands[i], ' '); // Split the command into arguments

		// printf("AFTER SPLIT - args[0]:%s\n", args[0]);
		// printf("\nAFTER SPLIT IN ARGS:\n");
		// print_args(args);
		// printf("\n");

// INPUT AND OUTPUT FILES INITIALIZED TO NULL / JA ESTAO INICIALIZADOS NO INITIALIZE_MAIN
		// parsed_struct[i].input_file = NULL;
		// parsed_struct[i].output_file = NULL;
		
		j = 0;

// LOOP ARGUMENTOS
		while (args[j] != NULL)
		{
			
// ERASE POSSIBLE QUOTES - ELIMINAR ASSIM QUE FIZER O GET_INPUT
			// printf("ERASE QUOTES ARGUMENTO[%s] \n", args[j]);
			ft_erase_quotes(args[j]);

//CHECK IF CURRENT ARG IS A REDIRECTION
			if (check_redir(args, j)) // RETURN 1 IF REDIRECTION, 0 IF NOT
			{
				if (x)
					printf("\nREDIRECTION [%s]\n\n", args[j]);
					
				parsed_struct = redirection(parsed_struct, args, i, j);
				
				if (x)
					print_struct(parsed_struct, i);
					
				j--;
			}
			else
			{
				if (x)
					printf("\nNO REDIRECTION [%s]\n\n", args[j]);
			}
			
			// printf("\nAFTER REDIRECTION:\n");
			// print_struct(parsed_struct, i);
			if (x)
				print_args(args);
			// printf("J LOOP ARGS: %d\n", j);
			// printf("\n");
			// exit(0);

//INCREMENT ARGUMENT INDEX
			j++;
		}

// ASSIGN COMMAND
		parsed_struct[i].cmd = args[0];
		if (x){
			printf("ASSIGNED COMMAND:%s\n\n", parsed_struct[i].cmd);	
			// print_struct(parsed_struct, i);
			// print_args(args);
			// printf("\n");
			}
	
// CHECK FLAGS
// "-" FLAGS
	if (args[1] && args[1][0] == '-')// Check if the second argument is a flag
	{
		// while (args[f] && args[f][0] == '-')
		// {
		// 	if (x)
		// 		printf("FLAGS\n");
		// 	parsed_struct[i].flags[f] = args[f];
		// 	// parsed_struct[i].args = copy_args(&args[f + 1]);
		// 	f++;	
		// }

		
		// {
			if (x)
				printf("FLAGS\n");
			// printf("args 1: %s\n", args[1]);
			// exit(0);
			parsed_struct[i].flags = args[1];
			// Saving the flags -- ANTES era ft_strdup(args[1])
			// printf("%s\n", parsed_commands[i].flags);
			parsed_struct[i].args = copy_args(&args[2]);
			// The rest are arguments
			// printf("%s\n", parsed_commands[i].flags);
		// }
	}
// NO FLAGS
	else
	{
		if (x)
			printf("NO FLAGS\n");
		parsed_struct[i].flags = NULL; // No flags
		parsed_struct[i].args = copy_args(&args[1]);
		// The rest are arguments
	}

// "|" PIPES
		if (i < num_commands - 1) //IF NOT THE LAST COMMAND, CREATE A PIPE
		{
			if (x)
				printf("PIPES\n");
				
			if (pipe (parsed_struct[i].fd) == -1) // Create a pipe
			{
				perror ("Pipe error"); // Print error message, in case of error
				exit (EXIT_FAILURE); // Exit the program
			}
		}
		
//INCREMENT COMMAND INDEX
	i++;
	}

// NULL TERMINATE THE ARRAY OF COMMANDS
	parsed_struct[num_commands].cmd = NULL;
	
	int w = 0;
	while (w < num_commands)
	{
		if (x){
			printf("\nSAIDA:\n");
			print_struct(parsed_struct, w);}
		w++;
	}	
	
// FREE MEMORY
	// free (commands);
	// printf("FREED COMMANDS\n");
	// free (changed);
	// printf("FREED CHANGED\n");
	// free (args);
	// printf("FREED ARGS\n");

	return (parsed_struct);
}

// cat <<EOF > outfile.txt
// cat <<EOF > output.txt


		// // PRINT PARSE_COMMANDS
		// 	printf("\nEND PARSED COMMANDS\n");
		// 	// printf("i: %d  /  j: %d  /  argv[j]: %s\n", i, j, args[j]);
		// 	printf("parsed_commands[i].cmd: %s\n", parsed_struct[i].cmd);
		// 	printf("parsed_commands[i].flags: %s\n", parsed_struct[i].flags);
		// // PRINT ARGS
		// 	int temp = j;
		// 	j = 0;
		// 	while (j <= count_args(parsed_struct[i].args))
		// 	{
		// 		if (parsed_struct[i].args && parsed_struct[i].args[j])
		// 		{
		// 			printf("parsed_commands[i].args[%d]: %s\n", j,
		// 				parsed_struct[i].args[j]);
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
		// 		parsed_struct[i].input_file);
		// 	printf("parsed_commands[i].output_file: %s\n",
		// 		parsed_struct[i].output_file);
		// 	printf("parsed_commands[i].heredoc: %s\n", parsed_struct[i].heredoc);
		// 	printf("parsed_commands[i].fd[0]: %d\n", parsed_struct[i].fd[0]);
		// 	printf("parsed_commands[i].fd[1]: %d\n", parsed_struct[i].fd[1]);
		// // end PRINT PARSE_COMMANDS




		//CHECAR PORQUE IMPRIME COMANDO NO FINAL SE TEM HEREDOC
		//CHECAR COMO LIDAR COM OS DIVERSOS FLAGS
		