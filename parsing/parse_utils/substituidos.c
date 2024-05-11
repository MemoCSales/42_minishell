/* ************************************************************************** */
/*                                                                            */
/*   substituidos.c             ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// =================================================

// NEW
// void process_command(char *command, char *changed)
// {
//     int i = 0, j = 0, in_string = 0;
//     while (command[i] != '\0')
//     {
//         if (command[i] == '"') in_string = !in_string;
//         if (!in_string && (command[i] == '>' || command[i] == '<')
// && command[i + 1] != ' ' && command[i + 1] != command[i])
//         {
//             changed[j++] = ' ';
//             changed[j++] = command[i];
//             changed[j++] = ' ';
//         }
//         else if (!in_string && command[i] == command[i + 1]
// && command[i + 2] != ' ')
//         {
//             changed[j++] = ' ';
//             changed[j++] = command[i];
//             changed[j++] = command[i++];
//             changed[j++] = ' ';
//         }
//         else changed[j++] = command[i];
//         i++;
//     }
//     changed[j] = '\0';
// }

// char	*insert_spaces(char *command)
// {
//     char	*changed;
//     int		i;
//     int		j;
//     int		in_string;

//     i = 0;
//     j = 0;
//     in_string = 0;
//     if (!command)
//     {
//         ft_putstr_fd("Error: No command specified\n", 2);
//         exit (1);
//     }
//     changed = malloc(strlen(command) * 5 + 1);
//     if (!changed)
//     {
//         ft_putstr_fd("Error: malloc failed\n", 2);
//         exit (1);
//     }
//     process_command(command, changed);
//     return (changed);
// }

// OLD
// char	*insert_spaces(char *command)
// {
// 	char	*changed;
// 	int		i;
// 	int		j;
// 	int		in_string;

// 	i = 0;
// 	j = 0;
// 	in_string = 0;
// 	if (!command)
// 	{
// 		ft_putstr_fd("Error: No command specified\n", 2);
// 		exit (1);
// 	}
// 	changed = malloc(strlen(command) * 5 + 1);
// 	if (!changed)
// 	{
// 		ft_putstr_fd("Error: malloc failed\n", 2);
// 		exit (1);
// 	}
// 	while (command[i] != '\0')
// 	{
// 		if (command[i] == '"')
// 		{
// 			in_string = !in_string;
// 		}
// 		if (!in_string && command[i] == '>'
// 			&& command[i + 1] != ' ' && command[i + 1] != '>')
// 		{
// 			changed[j++] = ' ';
// 			changed[j++] = '>';
// 			changed[j++] = ' ';
// 		}
// 		else if (!in_string && command[i] == '<'
// 			&& command[i + 1] != ' ' && command[i + 1] != '<')
// 		{
// 			changed[j++] = ' ';
// 			changed[j++] = '<';
// 			changed[j++] = ' ';
// 		}
// 		else if (!in_string && command[i] == '>'
// 			&& command[i + 1] == '>' && command[i + 2] != ' ')
// 		{
// 			changed[j++] = ' ';
// 			changed[j++] = '>';
// 			changed[j++] = '>';
// 			changed[j++] = ' ';
// 			i++;
// 		}
// 		else if (!in_string && command[i] == '<'
// 			&& command[i + 1] == '<' && command[i + 2] != ' ')
// 		{
// 			changed[j++] = ' ';
// 			changed[j++] = '<';
// 			changed[j++] = '<';
// 			changed[j++] = ' ';
// 			i++;
// 		}
// 		else
// 		{
// 			changed[j++] = command[i];
// 		}
// 		i++;
// 	}
// 	changed[j] = '\0';
// 	return (changed);
// }

// =================================================
// NEW
// char *read_heredoc(char *delimiter)
// {
//     char *heredoc;
//     char *line;
//     char *temp;

//     heredoc = NULL;
//     if (check_delimiter(delimiter))
//         return NULL;
//     while (1)
//     {
//         ft_putstr_fd("heredoc>", 1);
//         line = get_next_line(0);
//         if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
//             break;
//         if (heredoc == NULL)
//             heredoc = ft_strdup(line);
//         else
//         {
//             temp = ft_strjoin(heredoc, line);
//             free(heredoc);
//             heredoc = temp;
//         }
//         free(line);
//     }
//     free(line);
//     return (heredoc);
// }

// OLD
// char	*read_heredoc(char *delimiter)
// {
// 	char	*heredoc;
// 	char	*line;
// 	char	*temp;

// 	heredoc = NULL;
// 	if (!delimiter)
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
// 			STDERR_FILENO);
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		ft_putstr_fd("heredoc>", 1);
// 		line = get_next_line(0);
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			free (line);
// 			break ;
// 		}
// 		if (heredoc == NULL)
// 		{
// 			heredoc = ft_strdup(line);
// 		}
// 		else
// 		{
// 			temp = malloc(ft_strlen(heredoc) + ft_strlen(line) + 1);
// 			ft_strlcpy(temp, heredoc, ft_strlen(heredoc) + 1);
// 			ft_strlcat(temp, line, ft_strlen(heredoc) + ft_strlen(line) + 1);
// 			free(heredoc);
// 			heredoc = temp;
// 		}
// 		free (line);
// 	}
// 	return (heredoc);
// }

// =================================================
// NEW
// int check_delimiter(char *delimiter)
// {
//     if (!delimiter)
//     {
//         ft_putstr_fd("bash: syntax error near unexpected token
// `newline'\n", STDERR_FILENO);
//         return 1;
//     }
//     return 0;
// }

// char	*read_quotes(char *delimiter)
// {
//     char	*quotes;
//     char	*line;
//     char	*temp;

//     quotes = NULL;
//     if (check_delimiter(delimiter))
//         return (NULL);
//     while (1)
//     {
//         ft_putstr_fd("> ", 1);
//         line = get_next_line(0);
//         if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
//             break;
//         temp = quotes;
//         if (quotes)
//             quotes = ft_strjoin(temp, line);
//         else
//             quotes = ft_strdup(line);
//         free(temp);
//         free(line);
//     }
//     free(line);
//     return (quotes);
// }
// OLD
// char	*read_quotes(char *delimiter)
// {
// 	char	*quotes;
// 	char	*line;
// 	char	*temp;

// 	quotes = NULL;
// 	if (DEBUG)
// 		printf("ENTROU NO READ_QUOTES\n");
// 	if (!delimiter)
// 	{
// 		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
// 			STDERR_FILENO);
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		line = get_next_line(0);
// 		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			free (line);
// 			break ;
// 		}
// 		if (quotes == NULL)
// 		{
// 			quotes = ft_strdup(line);
// 		}
// 		else
// 		{
// 			temp = malloc(ft_strlen(quotes) + ft_strlen(line) + 1);
// 			ft_strlcpy(temp, quotes, ft_strlen(quotes) + 1);
// 			ft_strlcat(temp, line, ft_strlen(quotes) + ft_strlen(line) + 1);
// 			free(quotes);
// 			quotes = temp;
// 		}
// 		free (line);
// 	}
// 	if (DEBUG)
// 		printf("SAIU DO QUOTES:%s\n", quotes);
// 	return (quotes);
// }

// =================================================
// NEW
// void remove_quotes(char *arg) {
//     int len = ft_strlen(arg);
//     ft_memmove(arg, arg + 1, len - 1);
//     arg[len - 1] = '\0';
// }

// void clean_quotes(char **args) {
//     if (args[0]) {
//         int count = count_elements(args);
//         if ((count == 1 && !args[1]) || (args[1] && ((args[1][0]
// == '\"' && args[count - 1][ft_strlen(args[count - 1]) - 1] == '\"')
// || (args[1][0] == '\'' && args[count - 1][ft_strlen(args[count - 1])
// - 1] == '\'')))) {
//             if (args[0][0] == '\"' || args[0][0] == '\'') {
//                 remove_quotes(args[0]);
//             }
//             if (args[count - 1][ft_strlen(args[count - 1]) - 1]
// == '\"' || args[count - 1][ft_strlen(args[count - 1]) - 1] == '\'')
// {
//            args[count - 1][ft_strlen(args[count - 1]) - 1] = '\0';
//             }
//         }
//     }
// }

// CLEAN
// void	clean_quotes(char **args)
// {
// 	int		len;
// 	int		k;

// 	k = 0;
// 	if (args[0])
// 	{
// 		if ((count_elements(args) == 1) && !args[1])
// 		{
// 			if ((args[0][0] == '\"' && args[count_elements(args) - 1]
// 				[strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
// 				(args[0][0] == '\'' && args[count_elements(args) - 1]
// 				[strlen(args[count_elements(args) - 1]) - 1] == '\''))
// 			{
// 				if ((args[0][0] == '\"') || (args[0][0] == '\''))
// 				{
// 					len = ft_strlen(args[0]);
// 					while (k < len)
// 					{
// 						args[0][k] = args[0][k + 1];
// 						k ++;
// 					}
// 					args[0][len - 1] = '\0';
// 				}
// 				if ((args[count_elements(args) - 1][strlen(args[count_elements
// 								(args) - 1]) - 1] == '\"') ||
// 						(args[count_elements(args) - 1][strlen(args
// 						[count_elements(args) - 1]) - 1] == '\''))
// 				{
// 					len = strlen(args[count_elements(args) - 1]);
// 					args[count_elements(args) - 1][len - 1] = '\0';
// 				}
// 			}
// 		}
// 		if (args[1] && ((args[1][0] == '\"' && args[count_elements(args)
// 					- 1][strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
// 					(args[1][0] == '\'' && args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\'')))
// 		{
// 			if ((args[1][0] == '\"') || (args[1][0] == '\''))
// 			{
// 				len = strlen(args[1]);
// 				while (k < len)
// 				{
// 					args[1][k] = args[1][k + 1];
// 					k++;
// 				}
// 				args[1][len - 1] = '\0';
// 			}
// 			if ((args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\"')
// 				|| (args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\''))
// 			{
// 				len = strlen(args[count_elements(args) - 1]);
// 				args[count_elements(args) - 1][len - 1] = '\0';
// 			}
// 		}
// 	}
// }

// OLD
// void	clean_quotes(char **args)
// {
// 	int		len;
// 	int		k;

// 	k = 0;
// //IF IT HAS AT LEAST ONE ARGUMENT, AFTER THE SPLIT
// 	if (args[0])
// 	{
// 		if (DEBUG)
// 		{
// 			printf ("PRINT FIRST AND LAST CHARACTERS\n");
// 			printf ("args[0][0]: %c\n", args[0][0]);
// 			printf ("args[LAST]: %c\n\n", args[count_elements(args) - 1]
// 			[strlen(args[count_elements(args) - 1]) - 1]);
// 		}
// //IF JUST ONE ARGUMENT, AND HAVE QUOTES
// 		if (DEBUG)
// 			printf ("NUM ARGS: %d\n", count_elements(args));
// 		if ((count_elements(args) == 1) && !args[1])
// 		{
// 			if ((args[0][0] == '\"' && args[count_elements(args) - 1]
// 				[strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
// 				(args[0][0] == '\'' && args[count_elements(args) - 1]
// 				[strlen(args[count_elements(args) - 1]) - 1] == '\''))
// 			{
// 				if (DEBUG)
// 					printf("JUST ONE ARGUMENT AND HAVE QUOTES\n\n");
// // SHIFT LEFT INITIAL QUOTE
// 				if ((args[0][0] == '\"') || (args[0][0] == '\''))
// 				{
// 					len = ft_strlen(args[0]);
// 					while (k < len)
// 					{
// 						args[0][k] = args[0][k + 1];
// 						k ++;
// 					}
// 					args[0][len - 1] = '\0';
// 				}
// // TRIM FINAL QUOTE
// 				if ((args[count_elements(args) - 1][strlen(args[count_elements
// 								(args) - 1]) - 1] == '\"') ||
// 						(args[count_elements(args) - 1][strlen(args
// 						[count_elements(args) - 1]) - 1] == '\''))
// 				{
// 					len = strlen(args[count_elements(args) - 1]);
// 					args[count_elements(args) - 1][len - 1] = '\0';
// 				}
// 			}
// 			if (DEBUG)
// 			{
// 				printf("CLEANED QUOTES");
// 				print_args(args);
// 			}
// 		}
// // IF MORE THAN ONE ARGUMENT, AND FIRST AND LAST ARGUMENTS HAVE QUOTES
// 		if (args[1] && ((args[1][0] == '\"' && args[count_elements(args)
// 					- 1][strlen(args[count_elements(args) - 1]) - 1] == '\"') ||
// 					(args[1][0] == '\'' && args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\'')))
// 		{
// 			if (DEBUG)
// 				printf("FIRST AND LAST ARGUMENTS HAVE QUOTES\n\n");
// //ERASE INITIAL QUOTE
// 			if ((args[1][0] == '\"') || (args[1][0] == '\''))
// 			{
// 				len = strlen(args[1]);
// 				while (k < len)
// 				{
// 					args[1][k] = args[1][k + 1];
// 					k++;
// 				}
// 				args[1][len - 1] = '\0';
// 			}
// 			if (DEBUG)
// 			{
// 				printf("CLEANED INITIAL QUOTE:");
// 				print_args(args);
// 			}
// //ERASE FINAL QUOTE
// 			if ((args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\"')
// 				|| (args[count_elements(args) - 1]
// 					[strlen(args[count_elements(args) - 1]) - 1] == '\''))
// 			{
// 				len = strlen(args[count_elements(args) - 1]);
// 				args[count_elements(args) - 1][len - 1] = '\0';
// 			}
// 			if (DEBUG)
// 			{
// 				printf("CLEANED FINAL QUOTE:");
// 				print_args(args);
// 			}
// 		}
// 	}
// }

// NEW
// void	free_and_nullify(void **ptr)
// {
// 	if (*ptr)
// 	{
// 		free(*ptr);
// 		*ptr = NULL;
// 	}
// }

// void	free_parsed_struct(t_main *parsed_struct, int num_commands)
// {
// 	int	i;

// 	i = 0;
// 	while ((parsed_struct) && (i < num_commands))
// 	{
// 		free_and_nullify((void **)&parsed_struct[i].cmd);
// 		free_and_nullify((void **)&parsed_struct[i].flags);
// 		free_and_nullify((void **)&parsed_struct[i].args);
// 		free_and_nullify((void **)&parsed_struct[i].input_file);
// 		free_and_nullify((void **)&parsed_struct[i].output_file);
// 		free_and_nullify((void **)&parsed_struct[i].heredoc);
// 		free_and_nullify((void **)&parsed_struct[i].extra);
// 		if (parsed_struct[i].fd[0])
// 		{
// 			close(parsed_struct[i].fd[0]);
// 			parsed_struct[i].fd[0] = 0;
// 		}
// 		if (parsed_struct[i].fd[1])
// 		{
// 			close(parsed_struct[i].fd[1]);
// 			parsed_struct[i].fd[1] = 0;
// 		}
// 		i++;
// 	}
// 	free(parsed_struct);
// }

// OLD
// void	free_parsed_struct(t_main *parsed_struct, int num_commands)
// {
// 	int	i;

// 	i = 0;
// 	while ((parsed_struct) && (i < num_commands))
// 	{
// 		if (parsed_struct[i].cmd)
// 		{
// 			free(parsed_struct[i].cmd);
// 			parsed_struct[i].cmd = NULL;
// 		}
// 		if (parsed_struct[i].flags)
// 		{
// 			free(parsed_struct[i].flags);
// 			parsed_struct[i].flags = NULL;
// 		}
// 		if (parsed_struct[i].args)
// 		{
// 			free(parsed_struct[i].args);
// 			parsed_struct[i].args = NULL;
// 		}
// 		if (parsed_struct[i].input_file)
// 		{
// 			free(parsed_struct[i].input_file);
// 			parsed_struct[i].input_file = NULL;
// 		}
// 		if (parsed_struct[i].output_file)
// 		{
// 			free(parsed_struct[i].output_file);
// 			parsed_struct[i].output_file = NULL;
// 		}
// 		if (parsed_struct[i].heredoc)
// 		{
// 			free(parsed_struct[i].heredoc);
// 			parsed_struct[i].heredoc = NULL;
// 		}
// 		if (parsed_struct[i].extra)
// 		{
// 			free(parsed_struct[i].extra);
// 			parsed_struct[i].extra = NULL;
// 		}
// 		if (parsed_struct[i].fd[0])
// 		{
// 			close(parsed_struct[i].fd[0]);
// 			parsed_struct[i].fd[0] = 0;
// 		}
// 		if (parsed_struct[i].fd[1])
// 		{
// 			close(parsed_struct[i].fd[1]);
// 			parsed_struct[i].fd[1] = 0;
// 		}
// 		i++;
// 	}
// 	free(parsed_struct);
// 	parsed_struct = NULL;
// }

// ++++++++++++++++++++++++++++++++++++++++++++++++++
// int	in_quotes(char *line)
// {
// 	int	i;
// 	int	in_single_quotes;
// 	int	in_double_quotes;

// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '\'')
// 			in_single_quotes = !in_single_quotes;
// 		else if (line[i] == '\"' && (!in_double_quotes || line[i - 1] != '\\'))
// 			in_double_quotes = !in_double_quotes;
// 		i++;
// 	}
// 	if (in_single_quotes || in_double_quotes)
// 		return (-1);
// 	if (in_single_quotes)
// 		return (1);
// 	if (in_double_quotes)
// 		return (2);
// 	return (0);
// }

// OLD
// int	in_quotes(char *line)
// {
// 	int	i;
// 	int	in_single_quotes;
// 	int	in_double_quotes;
// 	int	result;

// 	result = 0;
// 	i = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if ((line[i] == '\'') && !in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 			{
// 				printf("INSIDE SINGLE QUOTES [%c] [%d]\n",
// 					line[i], in_single_quotes);
// 			}
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\'') && in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			if (DEBUG)
// 			{
// 				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n",
// 					line[i], in_single_quotes);
// 			}
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\"') && !in_double_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 			{
// 				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n",
// 					line[i], in_double_quotes);
// 			}
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\"') && in_double_quotes && (line[i - 1] != '\\'))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			if (DEBUG)
// 			{
// 				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n", line[i],
// 					in_double_quotes);
// 			}
// 			i++;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	if (in_single_quotes)
// 		result = 1;
// 	else if (in_double_quotes)
// 		result = 2;
// 	return (result);
// }

// =================================================
// OLD
// char	*prepared_input(char *line)
// {
// 	char	*prepared;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		len;
// 	int		in_single_quotes;
// 	int		in_double_quotes;
// 	char	*var_name;
// 	char	*var_value;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	var_name = malloc(256);
// 	check_malloc(var_name);
// 	prepared = malloc(ft_strlen(line) + 1);
// 	if (prepared == NULL)
// 	{
// 		free(var_name);
// 		return (NULL);
// 	}
// 	check_malloc(prepared);
// 	if (DEBUG)
// 		printf("LINE BEFORE: %s\n", line);
// 	while (line[i] != '\0')
// 	{
// 		if ((line[i] == '\'') && !in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("INSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n",
// 					line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\'') && in_single_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("OUTSIDE SINGLE QUOTES [%c]-IN SINGLE QUOTES [%d]\n",
// 					line[i], in_single_quotes);
// 			j++;
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\"') && !in_double_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("INSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n",
// 					line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue ;
// 		}
// 		if ((line[i] == '\"') && in_double_quotes && (line[i - 1] != '\\'))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			prepared[j] = line[i];
// 			if (DEBUG)
// 				printf("OUTSIDE DOUBLE QUOTES [%c]-IN DOUBLE QUOTES [%d]\n",
// 					line[i], in_double_quotes);
// 			j++;
// 			i++;
// 			continue ;
// 		}
// 		if (line[i] == '\"')
// 		{
// 			if (line[i - 1] == '\\')
// 			{
// 				if (DEBUG)
// 					printf("DOUBLE QUOTES WITH \\ BEFORE\n");
// 				strncpy(&prepared[j - 1], &line[i], strlen(&line[i]));
// 				i++;
// 			}
// 			continue ;
// 		}
// 		if (is_whitespace(line[i]) && !(in_single_quotes || in_double_quotes))
// 		{
// 			if (DEBUG)
// 				printf("WHITESPACE AND OUTSIDE QUOTES\n");
// 			prepared[j] = line[i];
// 			i++;
// 			j++;
// 			continue ;
// 		}
// 		if ((line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '\"'
// 					|| line[i + 1] == '\\')) && (in_double_quotes)
// 			&& (!in_single_quotes))
// 		{
// 			if (DEBUG)
// 				printf("ESCAPED CHARACTER INSIDE DOUBLE QUOTES \
// 				AND OUTSIDE SINGLE QUOTES\n");
// 			prepared[j] = line[i + 1];
// 			i += 2;
// 			j++;
// 			continue ;
// 		}
// 		if ((line[i] == '$' && !in_single_quotes) && (line[i - 1] != '\\'))
// 		{
// 			if (DEBUG)
// 				printf("DOLLAR SIGN OUTSIDE SINGLE QUOTES AND BEFORE NOT \\\n");
// 			if (var_name == NULL)
// 			{
// 				free(prepared);
// 				return (NULL);
// 			}
// 			i++;
// 			while (line[i] != '\0' && !is_whitespace(line[i]) && line[i] != '\''
// 				&& line[i] != '\"')
// 			{
// 				var_name[k] = line[i];
// 				i++;
// 				k++;
// 			}
// 			var_name[k] = '\0';
// 			var_value = getenv(var_name);
// 			if (var_value == NULL)
// 			{
// 				var_value = "";
// 			}
// 			if (strcmp(var_name, "?") == 0)
// 			{
// 				var_value = get_last_exit_status();
// 			}
// 			if (var_value != NULL)
// 			{
// 				len = strlen(var_value);
// 				strncpy(&prepared[j], var_value, len);
// 				j += len;
// 			}
// 			continue ;
// 		}
// 		else if (((line[i] == '$' && !in_single_quotes) && (line[i - 1]
// 					== '\\')) || ((line[i] == '$' && in_single_quotes)
// 				&& (line[i - 1] == '\\') && in_double_quotes))
// 		{
// 			if (DEBUG)
// 				printf("SE DOLLAR SIGN E FORA DE SINGLE QUOTES E ANTERIOR \\, \
// 				OU DOLLAR SIGN E DENTRO SINGLE QUOTES E ANTERIOR \\ E \
// 				DENTRO DOUBLE QUOTES\n");
// 			strncpy(&prepared[j - 1], &line[i], strlen(&line[i]));
// 			i++;
// 		}
// 		else if ((line[i] == '$' && in_single_quotes))
// 		{
// 			if (DEBUG)
// 				printf("DOLLAR SIGN INSIDE SINGLE QUOTES\n");
// 			prepared[j] = line[i];
// 			i++;
// 			j++;
// 			continue ;
// 		}
// 		prepared[j] = line[i];
// 		i++;
// 		j++;
// 	}
// 	prepared[j] = '\0';
// 	if (DEBUG)
// 		printf("LINE AFTER:  %s\n", prepared);
// 	free(var_name);
// 	return (prepared);
// }

// NEW

// char	*prepared_input(char *line)
// {
// 	char	*prepared;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		len;
// 	int		in_single_quotes;
// 	int		in_double_quotes;
// 	char	*var_name;
// 	char	*var_value;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	in_single_quotes = 0;
// 	in_double_quotes = 0;
// 	var_name = malloc(256);
// 	check_malloc(var_name);
// 	prepared = malloc(ft_strlen(line) + 1);
// 	if (prepared == NULL)
// 	{
// 		free(var_name);
// 		return (NULL);
// 	}
// 	check_malloc(prepared);
// 	while (line[i] != '\0')
// 	{
// 		if (((line[i] == '\'') && !in_single_quotes)
// 			|| ((line[i] == '\'') && in_single_quotes))
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			copy_increment(prepared, line, &i, &j);
// 			continue ;
// 		}
// 		if (((line[i] == '\"') && !in_double_quotes) || ((line[i] == '\"')
// 				&& in_double_quotes && (line[i - 1] != '\\')))
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			copy_increment(prepared, line, &i, &j);
// 			continue ;
// 		}
// 		if ((line[i] == '\"') && (line[i - 1] == '\\'))
// 		{
// 			ft_strncpy(&prepared[j - 1], &line[i], strlen(&line[i]));
// 			i++;
// 			continue ;
// 		}
// 		if (is_whitespace(line[i]) && !(in_single_quotes || in_double_quotes))
// 		{
// 			copy_increment(prepared, line, &i, &j);
// 			continue ;
// 		}
// 		if ((line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '\"'
// 					|| line[i + 1] == '\\')) && (in_double_quotes)
// 			&& (!in_single_quotes))
// 		{
// 			prepared[j] = line[i + 1];
// 			i += 2;
// 			j++;
// 			continue ;
// 		}
// 		if ((line[i] == '$' && !in_single_quotes) && (line[i - 1] != '\\'))
// 		{
// 			if (var_name == NULL)
// 			{
// 				free(prepared);
// 				return (NULL);
// 			}
// 			i++;
// 			while (line[i] != '\0' && !is_whitespace(line[i]) && line[i] != '\''
// 				&& line[i] != '\"')
// 			{
// 				var_name[k] = line[i];
// 				i++;
// 				k++;
// 			}
// 			var_name[k] = '\0';
// 			var_value = getenv(var_name);
// 			if (var_value == NULL)
// 			{
// 				var_value = "";
// 			}
// 			if (strcmp(var_name, "?") == 0)
// 			{
// 				var_value = get_last_exit_status();
// 			}
// 			if (var_value != NULL)
// 			{
// 				len = strlen(var_value);
// 				strncpy(&prepared[j], var_value, len);
// 				j += len;
// 			}
// 			continue ;
// 		}
// 		else if (((line[i] == '$' && !in_single_quotes) && (line[i - 1]
// 					== '\\')) || ((line[i] == '$' && in_single_quotes)
// 				&& (line[i - 1] == '\\') && in_double_quotes))
// 		{
// 			strncpy(&prepared[j - 1], &line[i], strlen(&line[i]));
// 			i++;
// 		}
// 		else if ((line[i] == '$' && in_single_quotes))
// 		{
// 			copy_increment(prepared, line, &i, &j);
// 			continue ;
// 		}
// 		copy_increment(prepared, line, &i, &j);
// 	}
// 	prepared[j] = '\0';
// 	free(var_name);
// 	return (prepared);
// }

// NEW PILOT
// void	handle_quotes(char *line, int *i, int *in_quotes)
// {
// 	if ((line[*i] == '\'' || line[*i] == '\"') && !is_escaped(line, *i))
// 	{
// 		if (*in_quotes == line[*i])
// 		{
// 			*in_quotes = 0;
// 		}
// 		else
// 		{
// 			*in_quotes = line[*i];
// 		}
// 		(*i)++;
// 	}
// }

// void	handle_variables(char *line, char *prepared, int *i, int *j)
// {
// 	char	var_name[256];

// 	if (line[*i] == '$' && (*i == 0 || line[*i - 1] != '\\'))
// 	{
// 		(*i)++;
// 		get_var_name(line, i, var_name);
// 		replace_var_value(var_name, prepared, j);
// 	}
// }

// void	handle_others(char *line, char *prepared, int *i, int *j)
// {
// 	if (line[*i] != '\0')
// 	{
// 		prepared[*j] = line[*i];
// 		(*j)++;
// 		(*i)++;
// 	}
// }

// void	handle_input(char *line, char *prepared)
// 	{
// 	int	i;
// 	int	j;
// 	int	in_quotes;

// 	i = 0;
// 	j = 0;
// 	in_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		handle_quotes(line, &i, &in_quotes);
// 		if (in_quotes != '\'')
// 		{
// 			handle_variables(line, prepared, &i, &j);
// 		}
// 		handle_others(line, prepared, &i, &j);
// 	}
// 	prepared[j] = '\0';
// }

// +++++++++++++++++++++++++++++++++++++++++++++++
// OLD 
// void	redirection(t_main *parsed_struct, char **args, int i, int j)
// {
// 	char	*delimiter;
// 	char	*heredoc;

// 	heredoc = NULL;
// 	if (DEBUG)
// 	{
// 		printf("\n\nREDIRECTION\n\n");
// 		print_args(args);
// 		printf("args[%d]: %s\n", j, args[j]);
// 	}
// 	if (ft_strcmp(args[j], ">>") == 0
// 		&& args[j + 1])
// 	{
// 		if (DEBUG)
// 			printf("ENTROU NO >> APPEND\n");
// 		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
// 		parsed_struct[i].extra = ft_strdup(args[j]);
// 		remove_args(args, j, 2);
// 	}
// 	else if (ft_strcmp(args[j], "<<") == 0
// 		&& args[j + 1])
// 	{
// 		if (DEBUG)
// 		{
// 			printf ("ENTROU NO << HEREDOC\n");
// 			printf("HEREDOC [J]: %d\n\n", j);
// 		}
// 		delimiter = args[j + 1];
// 		heredoc = read_heredoc(delimiter);
// 		parsed_struct[i].heredoc = heredoc;
// 		remove_args (args, j, 2);
// 	}
// 	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
// 	{
// 		if (DEBUG)
// 			printf("\n\"<\" INPUT \n\n");
// 		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
// 		remove_args(args, j, 2);
// 	}
// 	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
// 	{
// 		if (DEBUG)
// 			printf("\n\">\" OUTPUT\n\n");
// 		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
// 		remove_args(args, j, 2);
// 	}
// 	else
// 	{
// 		if (DEBUG)
// 			printf("\n\nARG NO WEIRD STUFF: %s\n", args[j]);
// 	}
// }

// NEW
// void	redirection(t_main *parsed_struct, char **args, int i, int j)
// {
// 	char	*delimiter;
// 	char	*heredoc;

// 	heredoc = NULL;
// 	if (ft_strcmp(args[j], ">>") == 0 && args[j + 1])
// 	{
// 		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
// 		parsed_struct[i].extra = ft_strdup(args[j]);
// 	}
// 	else if (ft_strcmp(args[j], "<<") == 0 && args[j + 1])
// 	{
// 		delimiter = args[j + 1];
// 		heredoc = read_heredoc(delimiter);
// 		parsed_struct[i].heredoc = heredoc;
// 	}
// 	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
// 	{
// 		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
// 	}
// 	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
// 	{
// 		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
// 	}
// 	remove_args(args, j, 2);
// }

// +++++++++++++++++++++++++++++++++++++++++++++++
// t_main	*parse_line(char *line)
// {
// 	t_main	*parsed_struct;
// 	char	**args;
// 	char	**commands;
// 	int		num_commands;
// 	int		i;
// 	int		j;
// 	int		f;
// 	int		k;
// 	int		len;
// 	int		w;

// 	w = 0;
// 	i = 0;
// 	j = 0;
// 	f = 1;
// 	k = 0;
// 	len = 0;
// //PREPARE INPUT
// 	line = prepared_input(line);
// 	if (DEBUG)
// 		printf("\nPREPARED INPUT:%s\n\n", line);
// //SPLIT LINE INTO COMMANDS
// 	commands = ft_split(line, '|');
// 	num_commands = count_elements(commands);
// 	if (DEBUG)
// 		printf("NUM COMMANDS: %d\n\n", num_commands);
// //INITIALIZE AND CHECK STRUCT
// 	parsed_struct = NULL;
// 	parsed_struct = initialize_main(parsed_struct, num_commands);
// //LOOP THE COMMANDS
// 	while (i < num_commands)
// 	{
// //CHANGE ARGUMENTS TO HAVE SPACES
// 		commands[i] = insert_spaces(commands[i]);
// 		if (DEBUG)
// 			printf("CHANGED:%s\n\n", commands[i]);
// //SPLIT COMMAND INTO ARGUMENTS
// 		args = ft_split(commands[i], ' ');
// 		if (DEBUG)
// 		{
// 			printf("SPLITTED:");
// 			print_args(args);
// 		}
// clean_quotes(args);
// 		if (DEBUG)
// 		{
// 			printf("CLEANED2:");
// 			print_args(args);
// 		}
// //LOOP ARGUMENTS
// 		j = 0;
// 		while (args[j] != NULL)
// 		{
// //CHECK IF CURRENT ARG IS A REDIRECTION
// 			if (check_redir(args, j))
// 			{
// 				redirection(parsed_struct, args, i, j);
// 				if (DEBUG)
// 				{
// 					printf("\nREDIRECTION [%s]\n\n", args[j]);
// 					print_struct(parsed_struct, i);
// 				}
// 				j--;
// 			}
// 			else
// 			{
// 				if (DEBUG)
// 					printf("\nNO REDIRECTION [%s]\n\n", args[j]);
// 			}
// 			if (DEBUG)
// 				print_args(args);
// 			j++;
// 		}
// // ASSIGN COMMAND
// 		parsed_struct[i].cmd = args[0];
// 		if (DEBUG)
// 		{
// 			printf("ASSIGNED COMMAND:%s\n\n", parsed_struct[i].cmd);
// 			print_struct(parsed_struct, i);
// 			print_args(args);
// 			printf("\n");
// 		}
// //CHECK FLAGS
// //-" FLAGS
// 		if (args[1] && args[1][0] == '-')
// 		{
// 			if (DEBUG)
// 				printf("FLAGS\n");
// 			parsed_struct[i].flags = args[1];
// 			parsed_struct[i].args = copy_args(&args[2]);
// 		}
// //NO FLAGS
// 		else
// 		{
// 			if (DEBUG)
// 			{
// 				printf("NO FLAGS\n");
// 			}
// 			parsed_struct[i].flags = NULL;
// 			parsed_struct[i].args = copy_args(&args[1]);
// 		}
// // "|" PIPES
// 		if (i < num_commands - 1)
// 		{
// 			if (DEBUG)
// 			{
// 				printf("PIPES\n");
// 			}
// 			if (pipe (parsed_struct[i].fd) == -1)
// 			{
// 				perror ("Pipe error");
// 				exit (EXIT_FAILURE);
// 			}
// 		}
// 		i++;
// 	}
// // NULL TERMINATE THE ARRAY OF COMMANDS
// 	parsed_struct[num_commands].cmd = NULL;
// 	while (w < num_commands)
// 	{
// 		if (DEBUG)
// 		{
// 			printf("\nSAIDA[%d]:\n", w);
// 			print_struct(parsed_struct, w);
// 			print_args(parsed_struct[w].args);
// 		}
// 		w++;
// 	}
// 	if (DEBUG)
// 	{
// 		printf ("RETURNING\n");
// 		print_args(parsed_struct[w - 1].args);
// 	}
// 	return (parsed_struct);
// }
// t_main	*parse_line(char *line)
// {
// 	t_main	*parsed_struct;
// 	char	**args;
// 	char	**commands;
// 	int		num_commands;
// 	int		i;

// 	i = 0;
// 	line = prepared_input(line);
// 	commands = ft_split(line, '|');
// 	num_commands = count_elements(commands);
// 	parsed_struct = NULL;
// 	parsed_struct = initialize_main(parsed_struct, num_commands);
// 	while (i < num_commands)
// 	{
// 		commands[i] = insert_spaces(commands[i]);
// 		args = ft_split(commands[i], ' ');
// 		clean_quotes(args);
// 		handle_redirections(parsed_struct, args, i);
// 		parsed_struct[i].cmd = args[0];
// 		check_flags(&parsed_struct[i], args);
// 		create_pipe(&parsed_struct[i], i, num_commands);
// 		i++;
// 	}
// 	parsed_struct[num_commands].cmd = NULL;
// 	return (parsed_struct);
// }
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// char	*ft_strncpy(char *dest, char *src, size_t n)
// {
// 	char	*sav_dest;
// 	char	*sav_src;

// 	if (n == 0)
// 		return (dest);
// 	if (dest == NULL && src == NULL)
// 		return (NULL);
// 	if (dest == NULL)
// 		return (src);
// 	if (src == NULL)
// 		return (dest);
// 	sav_dest = dest;
// 	sav_src = src;
// 	if (n != 0)
// 	{
// 		while (1)
// 		{
// 			*sav_dest = *sav_src++;
// 			if (*sav_dest++ == 0)
// 			{
// 				while (--n != 0)
// 					*sav_dest++ = 0;
// 				break ;
// 			}
// 			if (--n == 0)
// 				break ;
// 		}
// 	}
// 	return (dest);
// }
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++