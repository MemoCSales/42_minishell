/* ************************************************************************** */
/*                                                                            */
/*   exit.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_builtin(t_main *main)
{
	int	status;

	status = 0;
	status = determine_status_from_flags(main);
	if (status == 0)
		status = determine_status_from_args(main);
	perform_exit(main, status);
	return (status);
}

int	determine_status_from_flags(t_main *main)
{
	int	status;

	status = 0;
	if (main->flags != NULL)
		status = ft_atoi(main->flags);
	return (status);
}

int	exit_check_args(t_main *main)
{
	if (!main->args[0] || main->args[1] != NULL)
		return (handle_no_or_multiple_args(main));
	return (0);
}

void	perform_exit(t_main *main, int status)
{
	printf("exit\n");
	free(main->current_dir);
	exit(status);
}

int	ft_normal_exit(t_main *main)
{
	if (!main->args[0])
		printf("exit\n");
	else
	{
		error_messages("BASH_MANY_ARGUMENTS");
		return (1);
	}
	return (0);
}
