/* ************************************************************************** */
/*                                                                            */
/*   exec.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_fds_main(t_exec_context *context)
{
	if (context->i > 0)
	{
		if (context->main[context->i - 1].fd[0] != -1)
			close(context->main[context-> i - 1].fd[0]);
	}
	if (context->main[context->i].fd[1] != -1)
		close(context->main[context->i].fd[1]);
}

int	execute_with_commands(t_exec_context *context)
{
	if (context->main[context->i].cmd != NULL
		&& ft_strlen(context->main[context->i].cmd) > 0)
	{
		while (context->main[context->i].cmd != NULL)
		{
			if (builtins_no_output(context->main->cmd) != -1)
				return (context->env->status = exec_builtin(context->env,
						&context->main[context->i]));
			context->main[context->i].pid = fork();
			if (context->main[context->i].pid < 0)
				error_messages("ERROR_FORK");
			if (context->main[context->i].pid == 0)
				handle_child_process(context);
			else
				ft_close_fds_main(context);
			context->i++;
		}
		context->env->status = parent_process(context);
		return (context->env->status);
	}
	return (-1);
}

int	execute_without_commands(t_exec_context *context)
{
	if (context->main[context->i].cmd == NULL
		&& (context->main[context->i].input_file
			|| context->main[context->i].output_file
			|| context->main[context->i].heredoc))
	{
		context->env->status = exec_without_cmds(context);
		return (context->env->status);
	}
	else
	{
		context->env->status = 0;
		return (context->env->status);
	}
}

int	execute_command(t_env *env, t_main *main)
{
	t_exec_context	context;
	int				status;

	context.main = main;
	context.env = env;
	initialize_context(&context);
	status = execute_with_commands(&context);
	if (status != -1)
		return (status);
	return (execute_without_commands(&context));
}

int	exec_without_cmds(t_exec_context *context)
{
	if (context->main[context->i].heredoc != NULL)
	{
		context->heredoc_fd = handle_heredoc(context->main, context->i);
	}
	if ((context->main[context->i].input_file != NULL
			&& context->main[context->i].output_file != NULL)
		|| (context->main[context->i].heredoc != NULL
			&& context->main[context->i].output_file))
	{
		printf("HANDLE FILE REDIRECTION\n");
		handle_file_redirection(context->main, context->i, context->heredoc_fd);
	}
	if (context->heredoc_fd != -1)
		close(context->heredoc_fd);
	return (context->env->status);
}
