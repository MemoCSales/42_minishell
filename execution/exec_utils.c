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
	dir_paths = split_cmd_path(cmd_path);
	if (!dir_paths)
		return (NULL);
	while (dir_paths[i])
	{
		path_cmd = ft_strjoin(dir_paths[i], "/");
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
	cleanup_split(dir_paths);
	return (cmd_path);
}

void	pipe_redirection(t_exec_context *context)
{
	if (context->i != 0)
	{
		if (dup2(context->main[context->i - 1].fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 error");
			exit(EXIT_FAILURE);
		}
	}
	if (context->main[context->i + 1].cmd != NULL)
	{
		if (dup2(context->main[context->i].fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error");
			exit(EXIT_FAILURE);
		}
	}
}

void	exec_copy_args(t_main *main, char **exec_args, int i, int num_args)
{
	int	j;

	j = 0;
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
}

char	**build_exec_args(t_main *main, char **exec_args, int i)
{
	int	num_args;

	num_args = 0;
	while (main[i].args[num_args] != NULL)
		num_args++;
	exec_args = malloc((num_args + 3) * sizeof(char *));
	exec_copy_args(main, exec_args, i, num_args);
	return (exec_args);
}
