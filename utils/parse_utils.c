/* *************************************************************************** */
/*                                                                             */
/*                                                           ::     :::::      */
/*   parse_utils.c                                         :+:    :+:  :+:     */
/*                                                       +:+ +:+       +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>             +#+ +:+      +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>  +#+  +#+     +#+          */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#              */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr        */
/*                                                                             */
/* *************************************************************************** */

#include "../minishell.h"

char *space_output(char *command) // This function adds spaces around the '>' character
{
	char *changed;
	int i = 0;
	int j = 0;
	int in_string = 0;  // Boolean variable to keep track of whether we're inside a string

	changed = malloc(strlen(command) * 5 + 1);  // Allocate enough space for the preprocessed command
	if (!changed)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}

	while (command[i] != '\0') {
		if (command[i] == '"') {
			in_string = !in_string;  // Toggle the in_string variable
		}
		if (!in_string && command[i] == '>' && command[i + 1] != ' ')  // If '>' is not followed by a space and we're not inside a string
		{
			changed[j++] = ' ';
			changed[j++] = '>';
			changed[j++] = ' ';
		}
		else if (!in_string && command[i] == '<' && command[i + 1] != ' ')
		{
			changed[j++] = ' ';
			changed[j++] = '<';
			changed[j++] = ' ';
		}
		// else if (!in_string && command[i] == '>' && command[i + 1] != '>' && command[i + 2] != ' ')
		// {
		// 	changed[j++] = ' ';
		// 	changed[j++] = '>';
		// 	changed[j++] = '>';
		// 	changed[j++] = ' ';
		// }
		else
		{
			changed[j++] = command[i];
		}
		i++;
	}

	changed[j] = '\0';  // Null-terminate the preprocessed command
	return (changed);
}

t_main	*initialize_main(t_main *main_var, int num_commands)
{
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	if (!main_var)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	main_var->cmd = NULL;
	main_var->flags = NULL;
	main_var->args = NULL;
	main_var->input_file = NULL;
	main_var->output_file = NULL;
	main_var->heredoc = NULL;
	// main_var->fd[0] = 0;
	// main_var->fd[1] = 0;
	// main_var->pid = 0;
	return (main_var);
}

int ft_strcpy(char *dst, const char *src)
{
	int	i;

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

void test_parser()
{
	t_main *parsed_commands;

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