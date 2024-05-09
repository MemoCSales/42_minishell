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

#include "../minishell.h"

int		is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// //ANTIGA, AQUI POR SEGURANCA
char *prepared_input(char *line)
{
	char	*prepared;
	int		i;
	int		j;
	int		in_single_quotes;
	int		in_double_quotes;
	char	*var_name;
	char 	*var_value;
	int		x; // DEBUG
	
	x = 0; // DEBUG
	i = 0;
	j = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	var_name = malloc(256); // Assuming maximum variable name length is 256

	prepared = malloc(ft_strlen(line) + 1);
	check_malloc(prepared);

if (x)
		printf("LINE BEFORE: %s\n", line);
	
	while (line[i] != '\0')
	{
		//INSIDE SINGLE QUOTES
		if ((line[i] == '\'') && !in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			prepared[j] = line[i];
			if (x)
				printf("INSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n", line[i], in_single_quotes);
			j++;
			i++;
			continue;
		}

//OUTSIDE SINGLE QUOTES
		if ((line[i] == '\'') && in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			prepared[j] = line[i];
			if (x)
				printf("OUTSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n", line[i], in_single_quotes);
			j++;
			i++;
			continue;
		}

//INSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && !in_double_quotes)
		{
			in_double_quotes = !in_double_quotes;
			prepared[j] = line[i];
			if (x)
				printf("INSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n", line[i], in_double_quotes);
			j++;
			i++;
			continue;
		}

//OUTSIDE DOUBLE QUOTES
		if ((line[i] == '\"') && in_double_quotes && (line[i-1] != '\\'))
		{
			in_double_quotes = !in_double_quotes;
			prepared[j] = line[i];
			if (x)
				printf("OUTSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n", line[i], in_double_quotes);
			j++;
			i++;
			continue;
		}

		if (line[i] == '\"')
		{
			if (line[i-1] == '\\')
			{
				if (x)
					printf("DOUBLE QUOTES WITH \\ BEFORE\n");
				strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
				i++;
			}
			continue ;
		}

		if (is_whitespace(line[i]) && !(in_single_quotes || in_double_quotes))
		{
			if (x)
				printf("WHITESPACE AND OUTSIDE QUOTES\n");
			prepared[j] = line[i];
			i++;
			j++;
			continue ;
		}

		if ((line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == '\\')) &&
			(in_double_quotes) && (!in_single_quotes))
			{
				if (x)
					printf("ESCAPED CHARACTER INSIDE DOUBLE QUOTES AND OUTSIDE SINGLE QUOTES\n");
			prepared[j] = line[i+1];
			i += 2;
			j++;
			continue;
		}

		if ((line[i] == '$' && !in_single_quotes) && (line[i-1] != '\\'))
		{
			if (x)
				printf("DOLLAR SIGN OUTSIDE SINGLE QUOTES AND BEFORE NOT \\\n");

			if (var_name == NULL)
			{
				fprintf(stderr, "Memory allocation failed\n");
				exit(EXIT_FAILURE);
			}
			int k = 0;
			i++; // Skip the '$'
			while (line[i] != '\0' && !is_whitespace(line[i]) && line[i] != '\'' && line[i] != '\"') {
				var_name[k] = line[i];
				i++;
				k++;
			}
			var_name[k] = '\0';
			var_value = getenv(var_name);
			// char *var_value = getenv(var_name);
			if (var_value != NULL)
			{
				// Replace the variable with its value
				int len = strlen(var_value);
				strncpy(&prepared[j], var_value, len);
				j += len;
			}
			free(var_name);
			continue 	;
		}

		else if (((line[i] == '$' && !in_single_quotes) && (line[i-1] == '\\')) ||
				((line[i] == '$' && in_single_quotes) && (line[i-1] == '\\') && in_double_quotes))
		{
			if (x)
				printf("SE DOLLAR SIGN E FORA DE SINGLE QUOTES E ANTERIOR \\, OU DOLLAR SIGN E DENTRO SINGLE QUOTES E ANTERIOR \\ E DENTRO DOUBLE QUOTES\n");
			strncpy(&prepared[j-1], &line[i], strlen(&line[i]));
			i++;
		}

		else if ((line[i] == '$' && in_single_quotes))
		{
			if (x)
				printf("DOLLAR SIGN INSIDE SINGLE QUOTES\n");
			prepared[j] = line[i];
			i++;
			j++;
			continue;
		}

		prepared[j] = line[i];
		i++;
		j++;
	}
	prepared[j] = '\0';

if (x)
		printf("LINE AFTER:  %s\n", prepared);
// exit(0);
	return (prepared);
}

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
// 				printf("INSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
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
// 				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n", line[i], in_single_quotes);
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
// 				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
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
// 				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n", line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue;
// 		}

// // printf("SINGLE QUOTES: %d\nDOUBLE QUOTES: %d\n", in_single_quotes, in_double_quotes);

// // 	//CHECK FOR UNCLOSED QUOTES (0 = NO QUOTES, 1 = UNCLOSED SINGLE QUOTES, 2 = UNCLOSED DOUBLE QUOTES)
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
// 		printf("QUOTES - IN SINGLE QUOTES:%d / IN DOUBLE QUOTES:%d\n", in_single_quotes, in_double_quotes);}

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

// 		if ((line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == '\\')) &&
// 			(in_double_quotes) && (!in_single_quotes))
// 			{
// 				if (DEBUG){
// 					printf("ESCAPED CHARACTER INSIDE DOUBLE QUOTES AND OUTSIDE SINGLE QUOTES\n");}
// 			prepared[j] = line[i+1];
// 			i += 2;
// 			j++;
// 			continue;
// 		}

// 		if ((line[i] == '$' && !in_single_quotes) && (line[i-1] != '\\'))
// 		{
// 			if (DEBUG){
// 				printf("DOLLAR SIGN OUTSIDE SINGLE QUOTES AND BEFORE NOT \\\n");}

// 			if (var_name == NULL)
// 			{
// 				fprintf(stderr, "Memory allocation failed\n");
// 				exit(EXIT_FAILURE);
// 			}
// 			int k = 0;
// 			i++; // Skip the '$'
// 			while (line[i] != '\0' && !is_whitespace(line[i]) && line[i] != '\'' && line[i] != '\"') {
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

// 		else if (((line[i] == '$' && !in_single_quotes) && (line[i-1] == '\\')) ||
// 				((line[i] == '$' && in_single_quotes) && (line[i-1] == '\\') && in_double_quotes))
// 		{
// 			if (DEBUG){
// 				printf("SE DOLLAR SIGN E FORA DE SINGLE QUOTES E ANTERIOR \\,OU DOLLAR SIGN E DENTRO SINGLE QUOTES E ANTERIOR \\ E DENTRO DOUBLE QUOTES\n");}
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


//CREATE A CHILD PROCESS WITH EXIT STATUS 123, AND PRINT WEXITSTATUS (THE EXIT STATUS OF THE CHILD PROCESS),
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
