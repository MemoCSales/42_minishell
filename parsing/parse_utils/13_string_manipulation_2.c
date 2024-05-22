/* ************************************************************************** */
/*                                                                            */
/*   13_string_manipulation_2       ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	dup = NULL;
	len = strlen(s);
	if (n < len)
		len = n;
	dup = (char *)malloc(len + 1);
	if (dup)
	{
		memcpy(dup, s, len);
		dup[len] = '\0';
	}
	return (dup);
}

// ====================================================
// EXCLUIDOS
// ====================================================
// void	ft_erase_quotes(char *tkn)
// {
// 	int	i;
// 	int	double_q_flag;
// 	int	single_q_flag;

// 	i = 0;
// 	double_q_flag = 0;
// 	single_q_flag = 0;
// 	while (tkn[i])
// 	{
// 		if (tkn[i] == '"' && single_q_flag == 0)
// 		{
// 			double_q_flag = !double_q_flag;
// 			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
// 			continue ;
// 		}
// 		else if (tkn[i] == '\'' && double_q_flag == 0)
// 		{
// 			single_q_flag = !single_q_flag;
// 			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
// 			continue ;
// 		}
// 		i++;
// 	}
// }

// PARSE UTILS 5 ANTES DE MEXER
// #include "../minishell.h"

// void	remove_args_first_last_quotes(char *arg)
// {
// 	int	len;

// 	len = ft_strlen(arg);
// 	ft_memmove(arg, arg + 1, len - 1);
// 	arg[len - 1] = '\0';
// }

// void	clean_quotes(char **args)
// {
// 	int	count;

// 	count = 0;
// 	if (args[0])
// 	{
// 		count = count_elements(args);
// 		if ((count == 1 && !args[1]) || (args[1] && ((args[1][0] == '\"'
// 					&& args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"')
// 			|| (args[1][0] == '\'' && args[count - 1]
// 			[ft_strlen(args[count - 1]) - 1] == '\''))))
// 		{
// 			if (args[0][0] == '\"' || args[0][0] == '\'')
// 			{
// 				remove_args_first_last_quotes(args[0]);
// 			}
// 			if (args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"' ||
// 			args[count - 1][ft_strlen(args[count - 1]) - 1] == '\'')
// 			{
// 				args[count - 1][ft_strlen(args[count - 1]) - 1] = '\0';
// 			}
// 		}
// 	}
// }

// void	insert_spaces_in_command(char *command, char *changed, int *i, int *j)
// {
// 	int	in_string;

// 	in_string = 0;
// 	if (command[*i] == '"')
// 		in_string = !in_string;
// 	if (!in_string && (command[*i] == '>' || command[*i] == '<')
// 		&& command[*i + 1] != ' ' && command[*i + 1] != command[*i])
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = ' ';
// 	}
// 	else if (!in_string && command[*i] == command[*i + 1]
// 		&& command[*i + 2] != ' ' && command[*i] == '>'
// 		&& command[*i] == '<')
// 	{
// 		changed[(*j)++] = ' ';
// 		changed[(*j)++] = command[*i];
// 		changed[(*j)++] = command[*i];
// 		(*i)++;
// 		changed[(*j)++] = ' ';
// 	}
// 	else
// 		changed[(*j)++] = command[*i];
// 	(*i)++;
// }

// void	process_command(char *command, char *changed)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (command[i])
// 	{
// 		insert_spaces_in_command(command, changed, &i, &j);
// 	}
// 	changed[j] = '\0';
// }

// char	*insert_spaces(char *command)
// {
// 	char	*changed;

// 	if (!command)
// 	{
// 		ft_putstr_fd("Error: No command specified\n", 2);
// 		exit (1);
// 	}
// 	changed = malloc(strlen(command) * 5 + 1);
// 	check_malloc(changed);
// 	process_command(command, changed);
// 	return (changed);
// }
// ====================================================
// BASURA
// ====================================================
//START OF NEW PREPARED_INPUT
// char *prepared_input(char *line)
// {
// 	char	*prepared;
// 	char	*temp_char;
// 	int		i;
// 	int		j;
// 	int		temp_int;
// 	int		temp_s_quotes;
// 	int		temp_d_quotes;
// 	int		quotes;
// 	int		in_single_quotes;
// 	int		in_double_quotes;
// 	char	*var_name;
// 	char 	*var_value;

// 	i = 0;
// 	j = 0;
// 	temp_int = 0;
// 	temp_s_quotes = 0;
// 	temp_d_quotes = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	quotes = 0;
// 	var_name = malloc(256); // Assuming maximum variable name length is 256

// 	temp_char = NULL;
// 	prepared = malloc(ft_strlen(line) + 1);
// 	check_malloc(prepared);

// if (DEBUG){
// 		printf("LINE BEFORE:%s\n", line);}

// 	temp_int = i;

// 	while (line[i] != '\0')
// 	{

// //INSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && !in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("INSIDE SINGLE QUOTES [%c] [%d]\n",
// line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n",
// line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //INSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && !in_double_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n",
// line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n",
// line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// // printf("SINGLE QUOTES: %d\nDOUBLE QUOTES: %d\n",
// in_single_quotes, in_double_quotes);

// // 	//CHECK FOR UNCLOSED QUOTES (0 = NO QUOTES,
// 1 = UNCLOSED SINGLE QUOTES, 2 = UNCLOSED DOUBLE QUOTES)
// // 		quotes = in_quotes(line);

// // 		// if (DEBUG){
// // 			printf("QUOTES CHECK:%d\n", quotes);
// // 		// }

// // //IF QUOTES NOT CLOSED, READ THE REST, JOIN AND PRINT
// // 	//UNCLOSED SINGLE QUOTES
// // 		if (quotes == 1)
// // 		{	
// // 			if (DEBUG){
// // 				printf ("ERROR: UNCLOSED SINGLE QUOTES\n");}

// // 			temp_char = read_quotes("\'");

// // 			if (DEBUG)
// // 			{
// // 				printf("LINE:%s\n", line);
// // 				printf("TEMP:%s\n", temp_char);
// // 			}

// // 		//TRIM QUOTE
// // 			line = ft_strtrim(line, "\'");

// // 			if (DEBUG){
// // 				printf("TRIMMED:%s\n", line);}

// // 			line = ft_strjoin(line, "\n");
// // 			line = ft_strjoin(line, temp_char);

// // 			if (DEBUG){
// // 				printf("JOINED:%s\n", line);}

// // 		//PRINT JOINED
// // 			ft_putstr_fd("\033[1;31mψΨ:\033[0m", 0);
// // 			ft_putstr_fd(line, 0);
// // 			ft_putstr_fd(": command not found\n", 0);
// // 			exit(0);

// // 			// free(temp_char);

// // 			// if (DEBUG){
// // 			// 	printf("PREPARED SINGLE QUOTES:%s\n", line);}

// // 			// prepared = ft_strdup(line);
// // 			// break ;
// // 		}
// // 	//UNCLOSED DOUBLE QUOTES
// // 		else if (quotes == 2)
// // 		{
// // 			if (DEBUG){
// // 				printf ("ERROR: UNCLOSED DOUBLE QUOTES\n");}

// // 			temp_char = read_quotes("\"");
// // 			if (DEBUG)
// // 			{
// // 				printf("LINE:%s\n", line);
// // 				printf("TEMP:%s\n", temp_char);
// // 			}

// // 		// TRIM QUOTE
// // 			line = ft_strtrim(line, "\"");

// // 			if (DEBUG){
// // 				printf("TRIMMED:%s\n", line);}

// // 			line = ft_strjoin(line, "\n");
// // 			line = ft_strjoin(line, temp_char);

// // 			if (DEBUG){
// // 				printf("JOINED:%s\n", line);}

// // 		//PRINT JOINED
// // 			ft_putstr_fd("\033[1;31mψΨ:\033[0m", 0);
// // 			ft_putstr_fd(line, 0);
// // 			ft_putstr_fd(": command not found\n", 0);
// // 			exit(0);

// // 			// free(temp_char);

// // 			// if (DEBUG){
// // 			// 	printf("PREPARED DOUBLE QUOTES:%s\n", line);}

// // 			// prepared = ft_strdup(line);
// // 			// break ;
// // 		}

// // 		else if (quotes == 0)
// // 		{
// // 			if (DEBUG){
// // 				printf ("NO QUOTES\n");}

// // 			prepared = ft_strdup(line);
// // 			// i ++;
// // 			// continue ;
// // 		}
// // 		i++;
// 	}

// // 	i = temp_int;

// 	if (DEBUG){
// 		printf("PREPARED QUOTES:%s\n", prepared);
// 		printf("QUOTES - IN SINGLE QUOTES:%d / IN DOUBLE QUOTES:%d\n",
// in_single_quotes, in_double_quotes);}

//     line = ft_strdup(prepared);
// 	free(prepared);

// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\"')
// 		{
// 			if (line[i-1] == '\\')
// 			{
// 				if (DEBUG){
// 					printf("DOUBLE QUOTES WITH \\ BEFORE\n");}
// 				strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
// 				i++;
// 			}
// 			continue ;
// 		}

// 		if (is_whitespace(line[i]) && !(in_single_quotes || in_double_quotes))
// 		{
// 			if (DEBUG){
// 				printf("WHITESPACE AND OUTSIDE QUOTES\n");}
// 			prepared[j] = line[i];
// 			i++;
// 			j++;
// 			continue ;
// 		}

// 		if ((line[i] == '\\' && (line[i+1] == '\'' ||
// line[i+1] == '\"' || line[i+1] == '\\')) &&
// 			(in_double_quotes) && (!in_single_quotes))
// 			{
// 				if (DEBUG){
// 					printf("ESCAPED CHARACTER INSIDE DOUBLE
// QUOTES AND OUTSIDE SINGLE QUOTES\n");}
// 			prepared[j] = line[i+1];
// 			i += 2;
// 			j++;
// 			continue;
// 		}

// 		if ((line[i] == '$' && !in_single_quotes) && (line[i-1] != '\\'))
// 		{
// 			if (DEBUG){
// 				printf("DOLLAR SIGN OUTSIDE SINGLE QUOTES
// AND BEFORE NOT \\\n");}

// 			if (var_name == NULL)
// 			{
// 				fprintf(stderr, "Memory allocation failed\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			int k = 0;
// 			i++; // Skip the '$'
// 			while (line[i] != '\0' && !is_whitespace(line[i])
// && line[i] != '\'' && line[i] != '\"') {
// 				var_name[k] = line[i];
// 				i++;
// 				k++;
// 			}
// 			var_name[k] = '\0';
// 			var_value = getenv(var_name);
// 			// char *var_value = getenv(var_name);
// 			if (var_value != NULL)
// 			{
// 				// Replace the variable with its value
// 				int len = strlen(var_value);
// 				strncpy(&prepared[j], var_value, len);
// 				j += len;
// 			}
// 			free(var_name);
// 			continue 	;
// 		}

// 		else if (((line[i] == '$' && !in_single_quotes)
// && (line[i-1] == '\\')) ||
// 				((line[i] == '$' && in_single_quotes)
// && (line[i-1] == '\\') && in_double_quotes))
// 		{
// 			if (DEBUG){
// 				printf("SE DOLLAR SIGN E FORA DE SINGLE QUOTES
// E ANTERIOR \\,OU DOLLAR SIGN E DENTRO SINGLE QUOTES E ANTERIOR
// \\ E DENTRO DOUBLE QUOTES\n");}
// 			strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
// 			i++;
// 		}

// 		else if ((line[i] == '$' && in_single_quotes))
// 		{
// 			if (DEBUG){
// 				printf("DOLLAR SIGN INSIDE SINGLE QUOTES\n");}
// 			prepared[j] = line[i];
// 			i++;
// 			j++;
// 			continue;
// 		}

// 		prepared[j] = line[i];
// 		i++;
// 		j++;
// 	}
// 	prepared[j] = '\0';

// if (DEBUG){
// 		printf("LINE AFTER:%s\n", prepared);}
// 	return (prepared);
// }
//END OF NEW PREPARED_INPUT

// +++++++++++++++++++++++++++++++++++++++++++

//CREATE A CHILD PROCESS WITH EXIT STATUS 123, AND PRINT
// WEXITSTATUS (THE EXIT STATUS OF THE CHILD PROCESS),
//WTERMSIG (THE SIGNAL THAT CAUSED THE CHILD PROCESS TO TERMINATE), 
//WSTOPSIG (THE SIGNAL THAT CAUSED THE CHILD PROCESS TO STOP), 
//AND WCOREDUMP (WHETHER THE CHILD PROCESS PRODUCED A CORE DUMP).
// #include <sys/wait.h>
// #include <unistd.h>
// #include <stdio.h>

// int main() {
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Child process
//         return 123;  // Return an exit status
//     } else if (pid > 0) {
//         // Parent process
//         int status;
//         wait(&status);  // Wait for child to finish
//         if (WIFEXITED(status)) {
//             printf("Child exited with status %d\n", WEXITSTATUS(status));
//         }
//         if (WIFSIGNALED(status)) {
//             printf("Child was killed by signal %d\n", WTERMSIG(status));
//         }
//         if (WIFSTOPPED(status)) {
//             printf("Child is stopped by signal %d\n", WSTOPSIG(status));
//         }
//         if (WCOREDUMP(status)) {
//             printf("Child produced a core dump\n");
//         }
//     }
//     return 0;
// }

// ++++++++++++++++++++++++++++++++++++++++++++++++
//TO BLOCK KEYBOARD INPUT WHEN MAKING FILES
// #include <termios.h>
// #include <unistd.h>
// #include <stdio.h>

// int main() {
//     struct termios old_tio, new_tio;

//     /* get the terminal settings for stdin */
//     tcgetattr(STDIN_FILENO, &old_tio);

//     /* we want to keep the old setting to restore them at the end */
//     new_tio = old_tio;

//     /* disable canonical mode (buffered i/o) and local echo */
//     new_tio.c_lflag &=(~ICANON & ~ECHO);

//     /* set the new settings immediately */
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

//     printf("Keyboard input is blocked for 5 seconds...\n");
//     sleep(5);

//     /* restore the former settings */
//     tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

//     printf("Keyboard input is now enabled.\n");

//     return 0;
// }

// Create a script called start.sh to redirect the output:

// 	#!/bin/bash
// 	exec > /tmp/output.txt 2>&1

// Create a script called end.sh to restore the output
// and clear the redirected output:

// 	#!/bin/bash
// 	exec 1>/dev/tty
// 	exec 2>/dev/tty
// 	rm /tmp/output.txt

// In your Makefile, run start.sh at the beginning and end.sh at the end:

// all:
// 	./start.sh
// 	gcc -o myprogram myprogram.c
// 	./end.sh

// This will redirect all output (both stdout and stderr)
// to /tmp/output.txt while the gcc command is running.
// Once the gcc command is finished, the output will be
// restored to the terminal and the redirected output
// will be cleared.

// int		in_quotes(char *line)
// {
// 	int	i;
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;

// 	while (line[i] != '\0') //WHILE NOT THE END OF THE STRING
// 	{
// //INSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && !in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 				printf("INSIDE SINGLE QUOTES [%c] [%d]\n",
// line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE SINGLE QUOTES
// 		if ((line[i] == '\'') && in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n",
// line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //INSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && !in_double_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 				printf("INSIDE DOUBLE QUOTES [%c]
// [%d]\n", line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// //OUTSIDE DOUBLE QUOTES
// 		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n",
// line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}
// 	}

// 	if (in_single_quotes || in_double_quotes)
// 		return (1);
// 	return (0);
// }

// void	print_flags(char **flags)
// {
// 	int k;
// 	k= 0;
// 	printf("\n");
// 	while (flags[k] != NULL)
// 	{
// 		printf("Flag %d: %s\n", k, flags[k]);
// 		k++;
// 	}
// 	printf("\n");
// }

// char	*remove_args_first_last_quotes(char *str)
// {
// 	char	*new_str;
// 	int		i, j;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"')
// 			break;
// 		i++;
// 	}
// 	if (str[i] == '\0')
// 		return str;
// 	new_str = malloc(ft_strlen(str) + 1);
// 	if(!new_str)
// 	{
// 		perror("Error: Unable to allocate memory\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	j = 0;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != '\"')
// 		{
// 			new_str[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	return (new_str);
// }

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

// _++++++++++++++++++++++++++
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
// 	while (j <= count_elements(parsed_struct[i].args))
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

/* ************************************************************************** */
/*                                                                            */
/*   10_place_holder.c              ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// char* process_line(char *line)
// {
// 	int		*positions;
// 	char	*quoted_strings;
// 	char	*replaced_line;
// 	char	**split_strings;

// 	positions = find_double_quotes(line);
// 	check_malloc(positions);
// 	quoted_strings = get_quoted_strings(line, positions);
// 	check_malloc(quoted_strings);
// printf("Quoted strings00:%s\n", quoted_strings);
// 	replaced_line = replace_quoted_strings(line);
// 	if (check_double_quotes(positions))
// 	{
// 		printf("Warning: Unclosed double quote\n");
// 		free(positions);
// 		return (NULL);
// 	}
// 	if (replaced_line != NULL)
// 	{
// 		printf("Replaced line:%s\n", replaced_line);
// 	}
// 	free(positions);
// 	split_strings = ft_split(quoted_strings, '|');
// 	check_malloc(split_strings);
// 	print_args(split_strings);
// 	return (quoted_strings);
// }

// int* find_double_quotes(char *line)//RETURNS
// ARRAY OF POSITIONS OF DOUBLE QUOTES
// {
//     int count;
// 	int i;
// 	int j;
// 	int* result;

// 	count = 0;
// 	i = 0;
// 	j = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\"' && (i == 0 || line[i-1] != '\\'))
// 			count++;
// 		i++;
// 	}
// 	result = (int*)malloc((count + 1) * sizeof(int));
// 	check_malloc(result);
// 	i = 0;
// 	while (line[i] != '\0')
// 	{
//         if (line[i] == '\"' && (i == 0 || line[i-1] != '\\'))
//             result[j++] = i;
// 		i++;
//     }
// 	result[j] = -1; // End of array
// 	return (result);
// }

// int check_double_quotes(int* positions)//CHECKS IF DOUBLE QUOTES ARE CLOSED
// {
// 	int count;
// 	int i;

// 	count = 0;
// 	i = 0;
// 	while (positions[i] != -1)
// 	{
// 		count++;
// 		i++;
// 	}
// 	if (count % 2 != 0)
// 		return (1); // Unclosed double quote
// 	return (0); // All quotes are closed
// }

// char* allocate_memory(int* positions)
// {
//     int count = 0;
//     while (positions[count] != -1)
//         count++;
//     char* result = (char*)malloc((count / 2) * sizeof(char*));
// 	check_malloc(result);
// 	result[0] = '\0';  // Initialize result to an empty string
//     return result;
// }

// char* get_quoted_strings(char *line, int* positions)
// {
//     int i;
// 	int j;
// 	int start;
// 	int end;
//     int count;
//     char* result;

// 	i = 0;
// 	j = 0;
// 	count = 0;
// 	start = 0;
// 	end = 0;
// 	result = allocate_memory(positions);
//     while (i < count)
//     {
//         start = positions[i] + 1;
//         end = positions[i + 1] - 1;
//         char* substring = (char*)malloc((end - start + 2) * sizeof(char));
//         ft_strncpy(substring, line + start, end - start + 1);
//         substring[end - start + 1] = '\0';
//         ft_strcat(result, substring);  // Concatenate substring into result
//         free(substring);  // Free the memory allocated for substring
//         i += 2;
//     }
//     return (result);
// }

// char* replace_quoted_strings(char *line)
// {
//     int* positions = find_double_quotes(line);
//     if (positions == NULL)
// 	{
//         printf("Failed to allocate memory\n");
//         return NULL;
//     }
//     int unclosed = check_double_quotes(positions);
//     if (unclosed)
// 	{
//         printf("Warning: Unclosed double quote\n");
//         free(positions);
//         return NULL;
//     }
//     int total_length = strlen(line) + 1; // +1 for null terminator
//     char* result = malloc(total_length);
//     if (result == NULL)
// 	{
//         printf("Failed to allocate memory\n");
//         free(positions);
//         return NULL;
//     }
//     int result_index = 0;
//     int line_index = 0;
//     int i = 0;
//     int count = 0;
//     while (positions[i] != -1 && positions[i+1] != -1)
// 	{
//         // Copy characters before quote
//         while (line_index < positions[i])
// 		{
//             result[result_index] = line[line_index];
//             result_index++;
//             line_index++;
//         }
//         // Replace quoted string with placeholder
//         result_index += sprintf(result + result_index, "ΨψPH(%d)", count);
//         line_index = positions[i+1] + 1;
//         count++;
//         i += 2;
//     }
//     // Copy remaining characters
//     while (line[line_index] != '\0')
// 	{
//         result[result_index] = line[line_index];
//         result_index++;
//         line_index++;
//     }
//     result[result_index] = '\0'; // Add null terminator
//     free(positions);
//     return result;
// }
// // char* get_quoted_strings(char *line, int* positions)
// // {
// // 	int		total_length;
// // 	int		i;
// // 	int		count;
// // 	int		result_index;

// // 	total_length = 0;
// // 	i = 0;
// // 	count = 0;
// // 	result_index = 0;
// // 	while (positions[i] != -1 && positions[i+1] 
// != -1)//while int array is not at the end
// // 	{
// // 		int length = positions[i+1] - positions[i] 
// - 1; // Length of string between quotes
// // 		total_length += length;
// // 		// total_length += snprintf(NULL, 0, " 
// ΨψPH(0)(%d_%d_%d) ", positions[i], positions[i+1], 
// length); // Length of prefix
// // 		total_length += snprintf(NULL, 0, " 
// ΨψPH(%d) ", count); // Length of prefix
// // 		count++;
// // 		i += 2;
// // 	}
// // 	total_length += i/2; // Add space for '|' separators
// // 	char* result = malloc(total_length + 1); // +1 for null terminator
// // 	check_malloc(result);
// // 	i = 0;
// // 	count = 0;
// // 	while (positions[i] != -1 && positions[i+1] != -1)
// // 	{
// // 		int start = positions[i] + 1;
// // 		int end = positions[i+1];
// // 		// int length = end - start;
// // 		// result_index += sprintf(result + result_index, " 
// ΨψPH(%d)(%d_%d_%d) ", count, start, end, length); // Add prefix
// // 		result_index += sprintf(result + result_index, " 
// ΨψPH(%d)", count); // Add prefix
// // 		for (int j = start; j < end; j++)
// // 		{
// // 			result[result_index++] = line[j];
// // 		}
// // 		result[result_index++] = ' '; // Add space
// // 		result[result_index++] = '|'; // Add separator
// // 		i += 2;
// // 		count++;
// // 	}
// // 	result[result_index - 1] = '\0'; // 
// Replace last separator with null terminator
// // 	return (result);
// // }
