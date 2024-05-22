/* ************************************************************************** */
/*                                                                            */
/*   exec_utils_2.c             ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_context(t_exec_context *context)
{
	context->i = 0;
	context->exec_args = NULL;
	context->path_cmd = NULL;
	context->heredoc_fd = -1;
}

void	ft_close_fds(t_exec_context *context)
{
	int	j;

	j = 0;
	while (context->main[j].cmd)
	{
		if (context->i != j)
			close(context->main[j].fd[1]);
		if (context->i - 1 != j)
			close(context->main[j].fd[0]);
		j++;
	}
}

void	print_exec_args(char **exec_args)
{
	int	i;

	i = 0;
	while (exec_args[i])
	{
		printf("arg[%d]:%s\n", i, exec_args[i]);
		i++;
	}
}
