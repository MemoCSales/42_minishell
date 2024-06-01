/* ************************************************************************** */
/*                                                                            */
/*   general_utils_exit.c       ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_char(char first_char)
{
	if (!ft_isdigit(first_char) && first_char != '+' && first_char != '-')
	{
		error_messages("BASH_NUMERIC_ARGS");
		return (2);
	}
	return (0);
}

int	process_first_char(t_main *main, char first_char)
{
	int	status;

	status = 0;
	if (ft_isdigit(first_char) || first_char == '-' || first_char == '+')
	{
		if (first_char == '+')
			status = ft_atoi(main->args[0] + 1);
		else
			status = ft_atoi(main->args[0]);
	}
	else
	{
		error_messages("BASH_NUMERIC_ARGS");
		return (2);
	}
	return (status);
}

int	determine_status_from_args(t_main *main)
{
	int		status;
	char	first_char;

	status = exit_check_args(main);
	if (status != 0)
		return (status);
	first_char = main->args[0][0];
	status = check_first_char(first_char);
	if (status != 0)
		return (status);
	return (process_first_char(main, first_char));
}

int	handle_no_or_multiple_args(t_main *main)
{
	int	status;

	status = 0;
	status = ft_normal_exit(main);
	exit(status);
}