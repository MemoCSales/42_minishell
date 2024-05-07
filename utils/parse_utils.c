/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 03:03:21 by demacinema       ###   ########.fr       */
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

int	count_cmds(char **cmds)
{
	int	num_commands;

	if (!cmds)
		return (0);
	num_commands = 0;
	while (cmds[num_commands] != NULL)
		num_commands++;
	return (num_commands);
}

int	count_args(char **args)
{
	int	num_args;

	if (!args)
		return (0);
	num_args = 0;
	while (args[num_args] != NULL)
		num_args++;
printf ("NUM ARGS ARGS: %d\n", num_args);
	return (num_args);
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
	// printf("SAIU DO REMOVE_ARGS\n");
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

char	*read_heredoc(char *delimiter)
{
	char	*heredoc;
	char	*line;
	char	*temp;

	heredoc = NULL;
	if (!delimiter)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO);
		return (NULL);
	}
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		if (heredoc == NULL)
		{
			heredoc = ft_strdup(line);
		}
		else
		{
			temp = malloc(ft_strlen(heredoc) + ft_strlen(line) + 1);
			ft_strlcpy(temp, heredoc, ft_strlen(heredoc) + 1);
			ft_strlcat(temp, line, ft_strlen(heredoc) + ft_strlen(line) + 1);
			free(heredoc);
			heredoc = temp;
		}
		free (line);
	}
	// printf("SAIU DO HEREDOC\n");
	return (heredoc);
}

char	*insert_spaces(char *command)// adds spaces around the '>' character
{
	char	*changed;
	int		i;
	int		j;
	int		in_string;// keep track of whether we're inside a string
	i = 0;
	j = 0;
	in_string = 0;
	if (!command)
	{
		ft_putstr_fd("Error: No command specified\n", 2);
		exit (1);
	}
	changed = malloc(strlen(command) * 5 + 1);// for the preprocessed command
	if (!changed)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit (1);
	}
	while (command[i] != '\0')
	{
		if (command[i] == '"')
		{
			in_string = !in_string;// Toggle the in_string variable
		}
		if (!in_string && command[i] == '>'
			&& command[i + 1] != ' ' && command[i + 1] != '>')
		{
// printf("OK0>>\n");
			changed[j++] = ' ';
			changed[j++] = '>';
			changed[j++] = ' ';
		}
		else if (!in_string && command[i] == '<'
			&& command[i + 1] != ' ' && command[i + 1] != '<')
		{
// printf("OK1>>\n");
			changed[j++] = ' ';
			changed[j++] = '<';
			changed[j++] = ' ';
		}
		else if (!in_string && command[i] == '>'
			&& command[i + 1] == '>' && command[i + 2] != ' ')
		{
// printf("OK2>>\n");
			changed[j++] = ' ';
			changed[j++] = '>';
			changed[j++] = '>';
			changed[j++] = ' ';
			i++;
		}
		else if (!in_string && command[i] == '<'
			&& command[i + 1] == '<' && command[i + 2] != ' ')
		{
// printf("OK3>>\n");
			changed[j++] = ' ';
			changed[j++] = '<';
			changed[j++] = '<';
			changed[j++] = ' ';
			i++;
		}
		else
		{
			changed[j++] = command[i];
		}
		i++;
	}
	changed[j] = '\0';// Null-terminate the preprocessed command
// printf("changed: %s\n", changed);
// exit(0);
	return (changed);
}

t_main	*initialize_main(t_main *main_var, int num_commands)
{
	int	i;
	// if (num_commands <= 0)
	// {
	// 	ft_putstr_fd("Error: Invalid number of commands\n", 2);
	// 	exit (1);
	// }
	// if (!main_var)
	// {
	// 	ft_putstr_fd("Error: main_var is NULL\n", 2);
	// 	exit(1);
	// }

	i = 0;
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	check_malloc(main_var);
	
	while (i <= num_commands)
	{
		main_var->cmd = NULL;
		main_var->flags = NULL;
		main_var->args = NULL;
		main_var->input_file = NULL;
		main_var->output_file = NULL;
		main_var->heredoc = NULL;
		main_var->fd[0] = 0;
		main_var->fd[1] = 0;
		// main_var->pid = 0;
		i++;
	}
	return (main_var);
}

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	char	*sav_dest;
	char	*sav_src;

	if (n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == NULL)
		return (src);
	if (src == NULL)
		return (dest); // CHECK THESE ABOVE, IF CAUSES ANY ISSUES LATER
	sav_dest = dest;
	sav_src = src;
	if (n != 0)
	{
		while (1)
		{
			*sav_dest = *sav_src++;
			if (*sav_dest++ == 0)
			{
				while (--n != 0)
					*sav_dest++ = 0;
				break ;
			}
			if (--n == 0)
				break ;
		}
	}
	return (dest);
}

void	test_parser(void)
{
	t_main	*parsed_commands;

	// Test command with no arguments
	printf("Testing command with no arguments...\n");
	parsed_commands = parse_line("ls");
	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
	printf("Test passed.\n");
	// Test command with one argument
	printf("Testing command with one argument...\n");
	parsed_commands = parse_line("ls -l");
	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
	assert(strcmp(parsed_commands[0].flags, "-l") == 0);
	printf("Test passed.\n");
	// Test command with input redirection
	printf("Testing command with input redirection...\n");
	parsed_commands = parse_line("sort < file.txt");
	assert(strcmp(parsed_commands[0].cmd, "sort") == 0);
	assert(strcmp(parsed_commands[0].input_file, "file.txt") == 0);
	printf("Test passed.\n");
	// Test command with output redirection
	printf("Testing command with output redirection...\n");
	parsed_commands = parse_line("ls > file.txt");
	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
	assert(strcmp(parsed_commands[0].output_file, ">file.txt") == 0);
	printf("Test passed.\n");
	// Test command with output append redirection
	printf("Testing command with output append redirection...\n");
	parsed_commands = parse_line("ls >> file.txt");
	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
	assert(strcmp(parsed_commands[0].output_file, ">>file.txt") == 0);
	printf("Test passed.\n");
	// // Test command with heredoc
	// printf("Testing command with heredoc...\n");
	// parsed_commands = parse_line("cat << EOF");
	// assert(strcmp(parsed_commands[0].cmd, "cat") == 0);
	// assert(strcmp(parsed_commands[0].heredoc, "EOF") == 0);
	// printf("Test passed.\n");
	// // Test command with quotes
	// printf("Testing command with quotes...\n");
	// parsed_commands = parse_line("echo \"hello world\"");
	// assert(strcmp(parsed_commands[0].cmd, "echo") == 0);
	// assert(strcmp(parsed_commands[0].flags, "\"hello world\"") == 0);
	// printf("Test passed.\n");
	// Test command with multiple commands
	printf("Testing command with multiple commands...\n");
	parsed_commands = parse_line("ls -l | sort -r");
	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
	assert(strcmp(parsed_commands[0].flags, "-l") == 0);
	assert(strcmp(parsed_commands[1].cmd, "sort") == 0);
	assert(strcmp(parsed_commands[1].flags, "-r") == 0);
	printf("Test passed.\n");
}

// char	*remove_quotes(char *str)
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