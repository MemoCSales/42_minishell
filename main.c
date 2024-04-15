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


// t_main	*parse_line(char *line)
// {
// 	t_main	*parsed_commands;
// 	char	**args;
// 	char	**commands;
// 	int		num_commands;
// 	int		i;

// 	commands = ft_split(line, '|');
// 	num_commands = count_cmds(commands);
// 	// while (commands[num_commands] != NULL)
// 	// 	num_commands++;
// 	parsed_commands = malloc((num_commands + 1) * sizeof(t_main));
// 	if (!parsed_commands)
// 	{
// 		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < num_commands)
// 	{
// 		args = ft_split(commands[i], ' '); // Split the command into arguments
// 		parsed_commands[i].cmd = args[0];  // The first argument is the command
// 		if (args[1] && args[1][0] == '-') // Check if the second argument is a flag
// 		{
// 			parsed_commands[i].flags = args[1]; // Saving the flags
// 			parsed_commands[i].args = &args[2]; // The rest are arguments
// 		}
// 		else
// 		{
// 			parsed_commands[i].flags = NULL;    // No flags
// 			parsed_commands[i].args = &args[1]; // The rest are arguments
// 		}
// 		if (i < num_commands - 1)
// 		{
// 			if (pipe(parsed_commands[i].fd) == -1)
// 			{
// 				perror("Pipe error");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		i++;
// 	}
// 	parsed_commands[num_commands].cmd = NULL;
// 	free(commands);
// 	return (parsed_commands);
// }

// char	*get_env_path(t_env *env)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	while (env->env_vars[i] != NULL)
// 	{
// 		if (ft_strncmp(env->env_vars[i], "PATH=", 5) == 0)
// 		{
// 			path = env->env_vars[i] + 5;
// 			break;
// 		}
// 		i++;
// 	}
// 	return (path);
// }

// char	*get_cmd_path(t_main *main, char *cmd_path)
// {
// 	int	i;
// 	char	*prog;
// 	char	*path_cmd;
// 	char	**dir_paths;

// 	i = 0;
// 	dir_paths = ft_split(cmd_path, ':');
// 	while (dir_paths[i])
// 	{
// 		path_cmd = ft_strjoin(dir_paths[i], "/");
// 		prog = ft_strjoin(path_cmd, main->cmd);
// 		free(path_cmd);
// 		if (access(prog, F_OK | X_OK) == 0)
// 			return (prog);
// 		free(prog);
// 		i++;
// 	}
// 	cleanup_split(dir_paths);
// 	return (cmd_path); //check this later
// }

// void execute_piped_commands(t_main *main, t_env *env, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n - 1)
//     {
// 		main[i].pid = fork();
// 		if (main[i].pid == -1)
// 		{
// 			perror("Fork error");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (main[i].pid == 0) // Child process
// 		{
// 			if (i != 0) // Checks if there is a previous command
// 			{
// 				dup2(main[i].fd[0], STDIN_FILENO);
// 				close(main[i].fd[0]);
// 			}
// 			if (i < n - 1) //If not the last command
// 			{
// 				dup2(main[i].fd[1], STDOUT_FILENO);
// 				close(main[i].fd[1]);
// 			}
// 			// else // Last command
// 			// {
// 			// 	dup2(STDIN_FILENO, STDIN_FILENO);
// 			// 	// dup2(saved_stdin, STDIN_FILENO);
// 			// 	// close(saved_stdin);
// 			// }
// 			// close(main[i].fd[0]);
// 			// close(main[i].fd[1]);
// 			execute_command(env, &main[i]);
// 			// exit(EXIT_SUCCESS);
// 		}
// 		else // Parent process
// 		{
// 			close(main[i].fd[1]); // Close writting end of the pipe
// 			// close(main[i].fd[0]); // Close writting end of the pipe
// 			// if (in != 0)
// 			// 	close(in);
// 			// in = main[i].fd[0];
// 			// waitpid(main[i].pid, NULL, 0); // Waits for the children to finish
// 		}
// 		i++;
// 	}
// 	// if (in != 0)
// 	// 	dup2(in, STDIN_FILENO);
// 	// close(saved_stdin);
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		waitpid(main[i].pid, NULL, 0);
// 		i++;
// 	}
// }

// void	execute_command(t_env *env, t_main *main)
// {
// 	char    **exec_args;
// 	char	*path_env;
// 	char	*path_cmd;
// 	int     num_args;
// 	int     i;
// 	pid_t   pid;

// 	exec_args = NULL;
// 	if (buildins(main->cmd) != -1)
// 		exec_buildin(env, main);
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
// 			path_env = get_env_path(env);				// Prepare the env variables!
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


int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_main	*main_var;
	t_env	env_var;
	int		num_commands;

	(void)argc;
	(void)argv;
	init_env(&env_var, env); // This function initialize the env_vars
	while (1) // first while loop that prints a prompt and retrieves from what it reads
	{
		line = readline("\001\033[0;91m\002mini\001\033[1;91m\002ℍ\001\033[0;91m\002ΞLL>> \001\033[0m\002");
		// line = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
		// line = readline("minihell>>");
		if (ft_strlen(line) > 0)
			add_history(line);
		main_var = parse_line(line);
		num_commands = 0;
		while (main_var[num_commands].cmd)
			num_commands++;
		// print_struct(main_var); //printing parsing result
		// exit(0);
		if (num_commands >= 2)
			execute_piped_commands(main_var, &env_var, num_commands);
		else if (num_commands == 1)
		{
			if (buildins(main_var->cmd) == -1)
				execute_command(&env_var, main_var);
			else
				exec_buildin(&env_var, main_var);
		}
		// free_main(main_var); // This does not goes here
		free(line);
	}
	check_env(&env_var); // In this function it checks env_vars and frees the memory. Need to check if its needed
	return (0);
}
