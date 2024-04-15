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

void execute_piped_commands(t_main *main, t_env *env, int n)
{
	int	i;
	int	in;

	in = 0;
	i = 0;
	while (i < n - 1)
    {
		main[i].pid = fork();
		if (main[i].pid == -1)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		if (main[i].pid == 0) // Child process
		{
			if (i != 0) // Checks if there is a previous command
			{
				dup2(in, STDIN_FILENO);
				close(in);
			}
			if (i != n - 1) //If not the last command
			{
				dup2(main[i].fd[1], STDOUT_FILENO);
			}
			close(main[i].fd[0]);

			// else // Last command
			// {
			// 	dup2(STDIN_FILENO, STDIN_FILENO);
			// 	// dup2(saved_stdin, STDIN_FILENO);
			// 	// close(saved_stdin);
			// }
			// close(main[i].fd[0]);
			// close(main[i].fd[1]);
			execute_command(env, &main[i]);
			exit(EXIT_SUCCESS);
		}
		else // Parent process
		{
			close(main[i].fd[1]); // Close writting end of the pipe
			// close(main[i].fd[0]); // Close writting end of the pipe
			if (in != 0)
				close(in);
			in = main[i].fd[0];
			// waitpid(main[i].pid, NULL, 0); // Waits for the children to finish
		}
		i++;
	}
	i = 0;
	while (i < n - 1)
	{
		waitpid(main[i].pid, NULL, 0);
		i++;
	}
	if (in != 0)
		close(in);
}

void	execute_command(t_env *env, t_main *main)
{
	char    **exec_args;
	char	*path_env;
	char	*path_cmd;
	int     num_args;
	int     i;
	pid_t   pid;

	exec_args = NULL;
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
			path_env = get_env_path(env);				// Prepare the env variables!
			path_cmd = get_cmd_path(main, path_env);	// Find the full path of the command

			//Execute the command (you can use the pipex execution part)
			if (execve(path_cmd, exec_args, env->env_vars) == -1)
			{
				ft_putstr_fd("Command not found: ", 2);
				ft_putendl_fd(main->cmd, 2);
				exit(EXIT_FAILURE);
			}
		}
		else //Parent process waits for the child to finish
			waitpid(pid, NULL, 0);
	}
}
