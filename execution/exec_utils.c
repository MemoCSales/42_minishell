/* ************************************************************************** */
/*                                                                            */
/*   exec_utils.c               ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
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
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_main *main, char *cmd_path)
{
	int		i;
	char	*prog;
	char	*path_cmd;
	char	**dir_paths;

	i = 0;
	dir_paths = ft_split(cmd_path, ':');
	if (!cmd_path)
		return (NULL);
	while (dir_paths[i])
	{
		path_cmd = ft_strjoin(dir_paths[i], "/");
		// printf("%s\n", path_cmd);
		prog = ft_strjoin(path_cmd, main->cmd);
		free(path_cmd);
		if (access(prog, F_OK | X_OK) == 0)
		{
			cleanup_split(dir_paths);
			return (prog);
		}
		free(prog);
		i++;
	}
	free(prog);
	cleanup_split(dir_paths);
	// printf("Despues del cleanup\n");
	return (cmd_path); //check this later
}

int	pipe_redirection(t_main *main, int i)
{
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
	if (main[i + 1].cmd != NULL) // If not the last cmd,
					//redirect output to the next pipe
	{
		if (dup2(main[i].fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			exit(EXIT_FAILURE);
		}
		close(main[i].fd[0]);
		close(main[i].fd[1]);
		return (1);
	}
	return (0);
}

char	**build_exec_args(t_main *main, char **exec_args, int i)
{
	int	num_args;
	int	j;

	num_args = 0;
	while (main[i].args[num_args] != NULL)
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
			// if (ft_strcmp(main[i].args[j], "<") == 0
			// || ft_strcmp(main[i].args[j], ">") == 0)
			// {
			// 	printf("print < or >");
			// 	j++;
			// }
			exec_args[j + 1] = main[i].args[j];
			j++;
		}
		exec_args[num_args + 1] = NULL;
	}
	return (exec_args); //free memory from exec_args later on
}
