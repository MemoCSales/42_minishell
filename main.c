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

#include "minishell.h"

// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char	*cmd[] = {"echo","-n" "GREETING=HELLO, WORLD!", NULL}; //This variable is for testing the buildins
// 	char 	*rl;
// 	t_env	env_var;

// 	init_env(&env_var, env); //This function initialize the env_vars
// 	while (1) //first while loop that prints a prompt and retrieves from what it reads
// 	{
// 		rl = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
// 		printf("%s\n", rl);
// 		buildins(&env_var, cmd);
// 	}
// 	check_env(&env_var); //In this function it checks env_vars and frees the memory. Need to check if its needed
// 	return(0);
// }


//After calling this function with this input = echo Hello World
//The output is this one
// t_main parsed_commands[] = {
//     {
//         .cmd = "echo",
//         .args = {"echo", "Hello,", "world!", NULL}
//     },
//     {
//         .cmd = NULL
//     }
// };

t_main	*parse_line(char *line)
{
	t_main	*parsed_commands;
	char	**args;
	char 	**commands;
	int		num_commands;
	int		i;

	commands = ft_split(line, '|');
	num_commands = 0;
	while (commands[num_commands] != NULL)
		num_commands++;
	parsed_commands = malloc((num_commands + 1) * sizeof(t_main));
	if (!parsed_commands)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (i < num_commands)
	{
		args = ft_split(commands[i], ' '); //Split the command into arguments
		parsed_commands[i].cmd = args[0]; //The first argument is the command
		parsed_commands[i].args = args; //The entire array is the arguments
		i++;
	}
	parsed_commands[num_commands].cmd = NULL; //Setting the last element of the array as NULL
	free(commands);
	return (parsed_commands);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*line;
	t_main	*main_var;
	t_env	env_var;

	init_env(&env_var, env); //This function initialize the env_vars
	while (1) //first while loop that prints a prompt and retrieves from what it reads
	{
		line = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
		if (ft_strlen(line) > 0)
			add_history(line);
		main_var = parse_line(line);
		if(buildins(main_var->args) == -1)
			// execute_command(main_var->cmd);
			printf("Here it supposed to be a function\n");
		else
			exec_buildin(&env_var, main_var);
	}
	check_env(&env_var); //In this function it checks env_vars and frees the memory. Need to check if its needed
	return(0);
}

// void execute_command(t_main *main_var)
// {
//     pid_t pid = fork(); // Create a new process

//     if (pid < 0)
//     {
//         // Fork failed
//         perror("minishell");
//     }
//     else if (pid == 0)
//     {
//         // This is the child process
//         if (main_var->flags != NULL && strcmp(main_var->flags, ">") == 0)
//         {
//             // Handle output redirection
//             int fd = open(main_var->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd == -1)
//             {
//                 perror(main_var->args[1]);
//                 exit(EXIT_FAILURE);
//             }
//             dup2(fd, STDOUT_FILENO); // Redirect output to the file
//             close(fd);
//         }
//         if (execvp(main_var->cmd, main_var->args) < 0)
//         {
//             // execvp failed
//             perror(main_var->cmd);
//             exit(EXIT_FAILURE);
//         }
//     }
//     else
//     {
//         // This is the parent process
//         int status;
//         waitpid(pid, &status, 0); // Wait for the child process to finish
//     }
// }