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
	int		status;
	char	first_char;

	status = 0;
	if (main->flags != NULL)
		status = ft_atoi(main->flags);
	else if (!main->args[0] || main->args[1] != NULL)
	{
		status = ft_normal_exit(main);
		exit(status);
	}
	else
	{
		first_char = main->args[0][0];
		if (ft_isdigit(first_char) || first_char == '-' || first_char == '+')
			status = ft_atoi(main->args[0]);
		else
		{
			error_messages("BASH_NUMERIC_ARGS");
			return (2);
		}
	}
	printf("exit\n");
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
