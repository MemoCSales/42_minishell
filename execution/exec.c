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

char	*get_env_path(t_env *env)
{
	int		i;
	char	*path;

	i = 0;
	while (env->env_vars[i] != NULL)
	{
		if (ft_strncmp(env->env_vars[i], "PATH=", 5) == 0)
		{
			path = env->env_vars[i] + 5;
			break;
		}
		i++;
	}
	return (path);
}

char	*get_cmd_path(t_main *main, char *cmd_path)
{
	int	i;
	char	*prog;
	char	*path_cmd;
	char	**dir_paths;

	i = 0;
	dir_paths = ft_split(cmd_path, ':');
	while (dir_paths[i])
	{
		path_cmd = ft_strjoin(dir_paths[i], "/");
		prog = ft_strjoin(path_cmd, main->cmd);
		free(path_cmd);
		if (access(prog, F_OK | X_OK) == 0)
			return (prog);
		free(prog);
		i++;
	}
	cleanup_split(dir_paths);
	return (cmd_path); //check this later
}

void	execute_piped_commands(t_main *main, t_env *env, int n)
{
	int	i;
	int	in;

	i = 0;
	in = 0;
	while (i < n)
	{
		if (pipe(main->fd) == -1)
		{
			perror("Pipe error");
			exit(EXIT_FAILURE);
		}
		main->pid = fork();
		if (main->pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		if (main->pid == 0)
		{
			if (i != 0)
				dup2(in, STDIN_FILENO);
			if (i != n - 1)
				dup2(main->fd[1], STDOUT_FILENO);
			close(main->fd[0]);
			execute_command(env, &main[i]);
		}
		else
		{
			// waitpid(main->pid, NULL, 0);
			wait(NULL);
			close(main->fd[1]);
			if (in != 0)
				close(in);
			in = main->fd[0];
		}
		i++;
	}
}

// void execute_piped_commands(t_main *main, t_env *env, int n)
// {
//     int i;
//     int in = 0;
//     int fd[2];

// 	i = 0;
// 	while (i < n - 1)
//     {
//         pipe(fd);
//         if (fork() == 0)
//         {
//             dup2(in, 0); //change the input according to the old one 
//             dup2(fd[1], 1);
//             close(fd[0]);
//             if (in != 0) 
//                 close(in);
//             execute_command(env, &main[i]);
//             exit(EXIT_FAILURE);
//         }
//         else
//         {
//             wait(NULL); //wait for the child process to finish
//             close(fd[1]);
//             if (in != 0) 
//                 close(in);
//             in = fd[0]; //save the input for the next command
//         }
// 		i++;
//     }
//     if (in != 0)
//         dup2(in, 0);
//     execute_command(env, &main[i]);
// }

void	execute_command(t_env *env, t_main *main)
{
    char    **exec_args;
	char	*path_env;
	char	*path_cmd;
    int     num_args;
    int     i;
    pid_t   pid;

	if (buildins(main->cmd) != -1)
		exec_buildin(env, main);
	else
	{
		pid = fork();
		if (pid < 0)
			perror("Error: Unable to fork\n");
		if (pid == 0) //Child process
		{
			num_args = 0;
			while (main->args[num_args] != NULL)
				num_args++;
			// printf("%d\n", num_args);
			exec_args = malloc((num_args + 3) * sizeof(char *)); //Allocate memory for args + cmd, flags and NULL
			exec_args[0] = main->cmd;
			if (main->flags != NULL)
			{
				exec_args[1] = main->flags;
				i = 0;
				while (i < num_args)
				{
					exec_args[i + 2] = main->args[i];
					i++;
				}
				exec_args[num_args + 2] = NULL;
			}
			else
			{
				i = 0;
				while (i < num_args)
				{
					exec_args[i + 1] = main->args[i];
					i++;
				}
				exec_args[num_args + 1] = NULL;
			}
			path_env = get_env_path(env);	// Prepare the env variables!
			path_cmd = get_cmd_path(main, path_env);	// Find the full path of the command

			//Execute the command (you can use the pipex execution part)
			if (execve(path_cmd, exec_args, env->env_vars) == -1)
			{
				ft_putstr_fd("Command not found: ", 2);
				ft_putendl_fd(main->cmd, 2);
				exit(1);
			}
		}
		else //Parent process waits for the child to finish
			waitpid(pid, NULL, 0);
	}
}

// execute that handles redirections
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
