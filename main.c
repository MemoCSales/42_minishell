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

// typedef struct s_main
// {
// 	char	*cmd;
// 	char	*flags;
// 	char	**args;
// 	int		fd[2];
// 	pid_t	pid;
// }			t_main;

// typedef struct s_env
// {
// 	char	**env_vars;
// 	int		status;
// }			t_env;

// void	execute_piped_commands(t_main *main, t_env *env, int n)
// {
// 	int	i;
// 	int	in;

// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		if (pipe(main->fd) == -1)
// 		{
// 			perror("Pipe error");
// 			exit(EXIT_FAILURE);
// 		}
// 		main->pid = fork();
// 		if (main->pid < 0)
// 		{
// 			perror("Fork error");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (main->pid == 0)
// 		{
// 			dup2(in, STDIN_FILENO);
// 			dup2(main->fd[1], STDOUT_FILENO);
// 			close(main->fd[0]);
// 			if (in != 0)
// 				close(in);
// 			execute_command(env, &main[i]);
// 		}
// 		else
// 		{
// 			wait(NULL);
// 			close(main->fd[1]);
// 			in = main->fd[0];
// 		}
// 		i++;
// 	}
// 	if (in != 0)
// 		dup2(in, STDIN_FILENO);
// 	execute_command(env, &main[i]);
// }

// void	execute_command(t_env *env, t_main *main)
// {
//     char    **exec_args;
// 	char	*path_env;
// 	char	*path_cmd;
//     int     num_args;
//     int     i;
//     pid_t   pid;

// 	if (buildins(main->cmd) != -1)
// 	{
// 		exec_buildin(env, main);
// 	}
// 	else
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			perror("Error: Unable to fork\n");
// 		if (pid == 0) //Child process
// 		{
// 			num_args = 0;
// 			while (main->args[num_args] != NULL)
// 				num_args++;
// 			// printf("%d\n", num_args);
// 			exec_args = malloc((num_args + 3) * sizeof(char *)); //Allocate memory for args + cmd, flags and NULL
// 			exec_args[0] = main->cmd;
// 			if (main->flags != NULL)
// 			{
// 				exec_args[1] = main->flags;
// 				i = 0;
// 				while (i < num_args)
// 				{
// 					exec_args[i + 2] = main->args[i];
// 					i++;
// 				}
// 				exec_args[num_args + 2] = NULL;
// 			}
// 			else
// 			{
// 				i = 0;
// 				while (i < num_args)
// 				{
// 					exec_args[i + 1] = main->args[i];
// 					i++;
// 				}
// 				exec_args[num_args + 1] = NULL;
// 			}
// 			path_env = get_env_path(env);	// Prepare the env variables!
// 			path_cmd = get_cmd_path(main, path_env);	// Find the full path of the command

// 			//Execute the command (you can use the pipex execution part)
// 			if (execve(path_cmd, exec_args, env->env_vars) == -1)
// 			{
// 				ft_putstr_fd("Command not found: ", 2);
// 				ft_putendl_fd(main->cmd, 2);
// 				exit(1);
// 			}
// 		}
// 		else //Parent process waits for the child to finish
// 			waitpid(pid, NULL, 0);
// 	}
// }

// After calling this function with this input = echo Hello World
// The output is this one
// t_main parsed_commands[] = {
//     {
//         .cmd = "echo",
//			.flags = "-a",
//         .args = {"Hello,", "world!", NULL}
//     },
//     {
//         .cmd = NULL
//     }
// };
// SYNTAX: command [flags] [arguments]
t_main	*parse_line( char *line)
{
	t_main	*parsed_commands;
	char	**args;
	char	**commands;
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
		args = ft_split(commands[i], ' '); // Split the command into arguments
		parsed_commands[i].cmd = args[0];  // The first argument is the command
		if (args[1] && args[1][0] == '-') 
			// Check if the second argument is a flag
		{
			parsed_commands[i].flags = args[1]; // Saving the flags
			parsed_commands[i].args = &args[2]; // The rest are arguments
		}
		else
		{
			parsed_commands[i].flags = NULL;    // No flags
			parsed_commands[i].args = &args[1]; // The rest are arguments
		}
		i++;
	}
	parsed_commands[num_commands].cmd = NULL;
		// Setting the last element of the array as NULL
	free(commands);
	return (parsed_commands);
}

void	print_struct(t_main *main)
{
	int		i;
	char	**args;

	i = 0;
	while (main[i].cmd != NULL)
	{
		printf("Command: %s\n", main[i].cmd);
		if (main[i].flags != NULL)
			printf("Flags: %s\n", main[i].flags);
		if (main[i].args != NULL)
		{
			args = main[i].args;
			printf("Arguments: ");
			while (*args != NULL)
			{
				printf("%s ", *args);
				args++;
			}
			printf("\n");
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_main	*main_var;
	t_env	env_var;
	int		num_commands;

	(void)argc;
	(void)argv;
	init_env(&env_var, env); // This function initialize the env_vars
	while (1)               
		// first while loop that prints a prompt and retrieves from what it reads
	{
		line = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
		if (ft_strlen(line) > 0)
			add_history(line);
		main_var = parse_line(line);
		num_commands = 0;
		while (main_var[num_commands].cmd)
			num_commands++;
		// print_struct(main_var); //printing parsing result
		// exit(0);
		if (num_commands > 1)
			execute_piped_commands(main_var, &env_var, num_commands);
		else if (buildins(main_var->cmd) == -1)
			execute_command(&env_var, main_var);
		else
			exec_buildin(&env_var, main_var);
	}
	check_env(&env_var);
		// In this function it checks env_vars and frees the memory. Need to check if its needed
	return (0);
}
