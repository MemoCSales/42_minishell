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