/* ************************************************************************** */
/*                                                                            */
/*   redirections.c             ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parent_process(t_exec_context *context)
{
	int	i;

	i = 0;

	while (context->main[i].cmd != NULL)
	{
		close(context->main[i].fd[0]);
		close(context->main[i].fd[1]);
		waitpid(context->main[i].pid, &context->env->status, 0);
		i++;
	}
	return WEXITSTATUS(context->env->status);
}

void	handle_child_process(t_exec_context *context)
{
	exec_handle_redirections(context);
	context->exec_args = build_exec_args(context->main, context->exec_args, context->i);
	context->path_env = get_env_path(context->env);
	if (context->main[context->i].cmd[0] == '/' || ft_strncmp(context->main[context->i].cmd, "./", 2) == 0)
		context->path_cmd = ft_strdup(context->main[context->i].cmd);
	else
		context->path_cmd = get_cmd_path(&context->main[context->i], context->path_env);
	ft_close_fds(context);
	pipe_redirection(context);
	handle_grandson_process(context);
	if (context->heredoc_fd != -1)
		close(context->heredoc_fd);
	cleanup_split(context->exec_args);
	context->env->status = WEXITSTATUS(context->env->status);
	exit(context->env->status);
}

void	handle_grandson_process(t_exec_context *context)
{
	if (builtins_with_output(context->main[context->i].cmd) != -1)
	{
		free(context->path_cmd);
		context->env->status = exec_builtin(context->env, &context->main[context->i]);
	}
	else 
	{
		if (execve(context->path_cmd, context->exec_args, context->env->env_vars) == -1)
		{
			ft_putstr_fd(context->main[context->i].cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			context->env->status = EXEC_ERROR;
			exit(context->env->status);
		}
	}
}
