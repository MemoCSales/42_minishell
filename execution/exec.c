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

#include "../minishell.h"


// void    main_loop(t_env env_var, t_main *main_var)
// {
// 	char	*line;
// 	int		num_commands;
// 	while (1)			// first while loop that prints a prompt and retrieves from what it reads
// 	{
// 		line = readline("\001\033[0;91m\002mini\001\033[1;91m\002ℍ\001\033[0;91m\002ΞLL>> \001\033[0m\002");
// 		if (ft_strlen(line) > 0)
// 			add_history(line);
// 		main_var = parse_line(line);
// 		num_commands = 0;
// 		while (main_var[num_commands].cmd)
// 			num_commands++;
// 		// print_struct(main_var); // printing parsing result
// 		// printf("\n");
// 		// exit(0);
// 		if (num_commands >= 1)
// 		{
// 			if (buildins(main_var->cmd) == -1)
// 				execute_command(&env_var, main_var);
// 			else
// 				exec_buildin(&env_var, main_var);
// 		}
// 		// free_main(main_var); // This does not goes here
// 		free(line);
// 	}
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
// 			return (path);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_cmd_path(t_main *main, char *cmd_path)
// {
// 	int		i;
// 	char	*prog;
// 	char	*path_cmd;
// 	char	**dir_paths;

// 	i = 0;
// 	dir_paths = ft_split(cmd_path, ':');
// 	if (!cmd_path)
// 		return (NULL);
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

// // void	pipe_redirection(t_main *main, t_env *env_vars, int i)
// void	pipe_redirection(t_main *main, int i)
// {
// 	if (i != 0) // If not the first cmd, redirect input from the previous pipe
// 	{
// 		printf("%s\n", main[i].cmd);
// 		printf("%d\n", main[i].fd[0]);
// 		if (dup2(main[i - 1].fd[0], STDIN_FILENO) == -1) 
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(main[i - 1].fd[0]);
// 		close(main[i - 1].fd[1]);
// 	}
// 	if (main[i + 1].cmd != NULL) // If not the last cmd, redirect output to the next pipe
// 	{
// 		printf("%s\n", main[i].cmd);
// 		printf("%d\n", main[i].fd[1]);
// 		if (dup2(main[i].fd[1], STDOUT_FILENO) == -1) 
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(main[i].fd[0]);
// 		close(main[i].fd[1]);
// 	}
// 	// if (buildins(main[i].cmd) != -1)
// 	// {
// 	// 	exec_buildin(env_vars, &main[i]);
// 	// 	if (main[i + 1].cmd != NULL)
// 	// 		close(main[i].fd[1]);
// 	// 	exit(EXIT_SUCCESS);
// 	// }
// 	// 	else if (main[i + 1].cmd != NULL)
// 	// 		close(main[i].fd[1]);
// }

// char	**build_exec_args(t_main *main, char **exec_args, int i)
// {
// 	int	num_args;
// 	int	j;

// 	num_args = 0;
// 	while(main[i].args[num_args] != NULL)
// 		num_args++;
// 	exec_args = malloc((num_args + 3) * sizeof(char *));
// 	exec_args[0] = main[i].cmd;
// 	if (main[i].flags != NULL)
// 	{
// 		exec_args[1] = main[i].flags;
// 		j = 0;
// 		while (j < num_args)
// 		{
// 			exec_args[j + 2] = main[i].args[j];
// 			j++;
// 		}
// 		exec_args[num_args + 2] = NULL;
// 	}
// 	else
// 	{
// 		j = 0;
// 		while (j < num_args)
// 		{
// 			// if (ft_strcmp(main[i].args[j], "<") == 0 || ft_strcmp(main[i].args[j], ">") == 0)
// 			// {
// 			// 	printf("print < or >");
// 			// 	j++;
// 			// }
// 			exec_args[j + 1] = main[i].args[j];
// 			j++;
// 		}
// 		exec_args[num_args + 1] = NULL;
// 	}
// 	return (exec_args); //free memory from exec_args later on
// }

// void env_buildin(t_env *env_vars)
// {
// 	int	i;

// 	if (env_vars->env_vars == NULL)
// 	{
// 		printf("No environment variables available.\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (env_vars->env_vars[i] != NULL)
// 	{
// 		printf("%s\n", env_vars->env_vars[i]);
// 		// ft_putstr_fd(env_vars->env_vars[i], STDOUT_FILENO);
// 		// ft_putstr_fd("\n", STDOUT_FILENO);
// 		i++;
// 	}
// }
// // After calling this function with this input = echo Hello World
// // The output is this one
// // t_main parsed_commands[] = {
// //     {
// //         .cmd = "echo",
// //			.flags = "-a",
// //         .args = {"Hello,", "world!", NULL}
// //     },
// //     {
// //         .cmd = NULL
// //     }
// // };
// // SYNTAX: command [flags] [arguments]


// t_main	*parse_line(char *line)
// {
// 	t_main	*parsed_commands;
// 	char	**args;
// 	char	**commands;
// 	int		num_commands;
// 	int		i;
// 	int		j;

// 	commands = ft_split(line, '|');
// 	num_commands = count_cmds(commands);
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
// 		parsed_commands[i].input_file = NULL;
// 		parsed_commands[i].output_file = NULL;
// 		j = 0;
// 		while (args[j] != NULL)
// 		{
// 			args[j] = remove_quotes(args[j]);
// 			if (ft_strcmp(args[j], "<") == 0)
// 			{
// 				parsed_commands[i].input_file = args[j + 1];
// 				remove_args(args, j, 2);
// 			}
// 			else if (ft_strcmp(args[j], ">") == 0)
// 			{
// 				parsed_commands[i].output_file = args[j + 1];
// 				remove_args(args, j, 2);
// 			}
// 			else
// 				j++;
// 		}
// 		parsed_commands[i].cmd = args[0];  // Assigning command
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




/*---------------------------------------------------*/

void	print_exec_args(char **exec_args)
{
	int	i;
	// int	j;

	i = 0;
	while (exec_args[i])
	{
		printf("arg[%d]:%s\n", i, exec_args[i]);
		i++;
	}
}

// int	check_for_redirect_output(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while(main->args[i] != NULL)
// 	{
// 		if (ft_strcmp(main->args[i], ">") == 0)
// 			return (1);	// ">" is present in the args
// 		i++;
// 	}
// 	return (0); // ">" Not found
// }

// int	check_for_redirect_input(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while(main->args[i] != NULL)
// 	{
// 		if (ft_strcmp(main->args[i], "<") == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


void	handle_output_redirection(t_main *main, int i)
{
	int	fd;
	// int	redirect_output;

	// redirect_output = check_for_redirect_output(&main[i]);
	if(main[i].output_file != NULL)
	{
		// printf("Output file: %s\n", main[i].output_file);
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error: Unable to open file\n");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_input_redirection(t_main *main, int i)
{
	int fd;

	if (main[i].input_file != NULL)
	{
		// printf("Input file: %s\n", main[i].input_file);
		fd = open(main[i].input_file, O_RDONLY);
		if (fd < 0)
		{
			// perror("");
			ft_putstr_fd("zsh: no such file or directory: ", 2);
			ft_putstr_fd(main[i].input_file, 2);
			ft_putstr_fd("\n", 2);
			// close(fd);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	parent_process(t_main *main, t_env *env, int i)
{
	if (i != 0) // If not the 1st cmd, closes the ends of the previous pipe
	{
		close(main[i - 1].fd[0]);
		close(main[i - 1].fd[1]);
	}
	waitpid(main[i].pid, &env->status, 0);
}

void	execute_command(t_env *env, t_main *main)
{
	char    **exec_args;
	char	*path_env;
	char	*path_cmd;
	int     i;

	exec_args = NULL;
	// if (buildins(main->cmd) != -1)
	// 	exec_buildin(env, main);
	// else
	// {
		i = 0;
		while (main[i].cmd != NULL)
		{
			main[i].pid = fork();
			if (main[i].pid < 0)
			{
				perror("Error: Unable to fork\n");
				exit(EXIT_FAILURE);
			}
			if (main[i].pid == 0) //Child process
			{
				pipe_redirection(main, i);
				if (main[i].input_file != NULL)
					handle_input_redirection(main, i);
				if (main[i].output_file != NULL)
					handle_output_redirection(main, i);
				exec_args = build_exec_args(main, exec_args, i);
				path_env = get_env_path(env);					// Prepare the env variables!
				path_cmd = get_cmd_path(&main[i], path_env);	// Find the full path of the command
				// print_exec_args(exec_args);
				if (buildins(main->cmd) != -1)
				{
					exec_buildin(env, &main[i]);
					exit(EXIT_SUCCESS);
				}
				if (execve(path_cmd, exec_args, env->env_vars) == -1)
				{
					ft_putstr_fd("zsh: command not found: ", 2);
					ft_putendl_fd(main[i].cmd, 2);
					exit(EXIT_FAILURE);
				}
			}
			else // Parent process
				parent_process(main, env, i);
			i++;
		}
	}
// }
