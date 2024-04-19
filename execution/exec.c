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

void	execute_command(t_env *env, t_main *main)
{
	char    **exec_args;
	char	*path_env;
	char	*path_cmd;
	int     num_args;
	int     i;
	int		j;

	exec_args = NULL;
	if (buildins(main->cmd) != -1)
		exec_buildin(env, main);
	else
	{
		i = 0;
		while (main[i].cmd != NULL)
		{
			// printf("Execution command: %s\n", main[i].cmd);
			main[i].pid = fork();
			if (main[i].pid < 0)
			{
				perror("Error: Unable to fork\n");
				exit(EXIT_FAILURE);
			}
			if (main[i].pid == 0) //Child process
			{
				// printf("Inside child process for command: %s\n", main[i].cmd);
				if (i != 0) // If not the first cmd, redirect input from the previous pipe
				{
					if (dup2(main[i - 1].fd[0], STDIN_FILENO) == -1) 
					{
						perror("dup2 error");
						exit(EXIT_FAILURE);
					}
					close(main[i - 1].fd[0]);
					close(main[i - 1].fd[1]);
				}
				if (main[i + 1].cmd != NULL) // If not the last cmd, redirect output to the next pipe
				{
					if (dup2(main[i].fd[1], STDOUT_FILENO) == -1) 
					{
						perror("dup2 error");
						exit(EXIT_FAILURE);
					}
					// printf("After dup2 Output pipe: %d\n", main[i].fd[1]);
					close(main[i].fd[0]);
					close(main[i].fd[1]);
				}
				// printf("Input pipe: %d\n", main[i].fd[0]);
				// printf("Output pipe: %d\n", main[i].fd[1]);
				num_args = 0;
				while(main[i].args[num_args] != NULL)
					num_args++;
				exec_args = malloc((num_args + 3) * sizeof(char *));
				exec_args[0] = main[i].cmd;
				if (main[i].flags != NULL)
				{
					exec_args[1] = main[i].flags;
					j = 0;
					while (j < num_args)
					{
						exec_args[j + 2] = main[i].args[j];
						j++;
					}
					exec_args[num_args + 2] = NULL;
				}
				else
				{
					j = 0;
					while (j < num_args)
					{
						exec_args[j + 1] = main[i].args[j];
						j++;
					}
					exec_args[num_args + 1] = NULL;
				}
				path_env = get_env_path(env);				// Prepare the env variables!
				path_cmd = get_cmd_path(&main[i], path_env);	// Find the full path of the command
				// printf("Exec args:");
				// for (int k = 0; k < num_args + 3; k++) {
				// 	printf(" %s", exec_args[k]);
				// }
				if (execve(path_cmd, exec_args, env->env_vars) == -1)
				{
					ft_putstr_fd("Command not found: ", 2);
					ft_putendl_fd(main->cmd, 2);
					exit(EXIT_FAILURE);
				}
			}
			else // Parent process
			{
				if (i != 0) // If not the 1st cmd, close the preivous pipe
				{
					close(main[i - 1].fd[0]);
					close(main[i - 1].fd[1]);
				}
				if (main[i + 1].cmd != NULL)
				{
					close(main[i].fd[1]);
				}
				waitpid(main[i].pid, &env->status, 0);
			}
			i++;
		}
	}
}
