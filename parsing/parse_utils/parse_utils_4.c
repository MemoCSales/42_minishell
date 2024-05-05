/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_4.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//COUNTERS
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
	return (num_args);
}

//LIBFTERS
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

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*ptr;
	char	*src_ptr;

	ptr = dest;
	src_ptr = (char *)src;
	if (n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == NULL)
		return (src_ptr);
	if (src == NULL)
		return (dest);
	while (*src && n)
	{
		*ptr++ = *src++;
		n--;
	}
	while (n--)
		*ptr++ = '\0';
	return (dest);
}
// //TESTERS
// void	test_parser(void)
// {
// 	t_main	*parsed_commands;

// 	// Test command with no arguments
// 	printf("Testing command with no arguments...\n");
// 	parsed_commands = parse_line("ls");
// 	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
// 	printf("Test passed.\n");
// 	// Test command with one argument
// 	printf("Testing command with one argument...\n");
// 	parsed_commands = parse_line("ls -l");
// 	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
// 	assert(strcmp(parsed_commands[0].flags, "-l") == 0);
// 	printf("Test passed.\n");
// 	// Test command with input redirection
// 	printf("Testing command with input redirection...\n");
// 	parsed_commands = parse_line("sort < file.txt");
// 	assert(strcmp(parsed_commands[0].cmd, "sort") == 0);
// 	assert(strcmp(parsed_commands[0].input_file, "file.txt") == 0);
// 	printf("Test passed.\n");
// 	// Test command with output redirection
// 	printf("Testing command with output redirection...\n");
// 	parsed_commands = parse_line("ls > file.txt");
// 	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
// 	assert(strcmp(parsed_commands[0].output_file, ">file.txt") == 0);
// 	printf("Test passed.\n");
// 	// Test command with output append redirection
// 	printf("Testing command with output append redirection...\n");
// 	parsed_commands = parse_line("ls >> file.txt");
// 	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
// 	assert(strcmp(parsed_commands[0].output_file, ">>file.txt") == 0);
// 	printf("Test passed.\n");
// 	// // Test command with heredoc
// 	// printf("Testing command with heredoc...\n");
// 	// parsed_commands = parse_line("cat << EOF");
// 	// assert(strcmp(parsed_commands[0].cmd, "cat") == 0);
// 	// assert(strcmp(parsed_commands[0].heredoc, "EOF") == 0);
// 	// printf("Test passed.\n");
// 	// // Test command with quotes
// 	// printf("Testing command with quotes...\n");
// 	// parsed_commands = parse_line("echo \"hello world\"");
// 	// assert(strcmp(parsed_commands[0].cmd, "echo") == 0);
// 	// assert(strcmp(parsed_commands[0].flags, "\"hello world\"") == 0);
// 	// printf("Test passed.\n");
// 	// Test command with multiple commands
// 	printf("Testing command with multiple commands...\n");
// 	parsed_commands = parse_line("ls -l | sort -r");
// 	assert(strcmp(parsed_commands[0].cmd, "ls") == 0);
// 	assert(strcmp(parsed_commands[0].flags, "-l") == 0);
// 	assert(strcmp(parsed_commands[1].cmd, "sort") == 0);
// 	assert(strcmp(parsed_commands[1].flags, "-r") == 0);
// 	printf("Test passed.\n");
// }

//ANTIGAS

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
// 		return (dest); // CHECK THESE ABOVE, IF CAUSES ANY ISSUES LATER
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
