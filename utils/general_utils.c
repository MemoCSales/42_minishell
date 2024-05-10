/* ************************************************************************** */
/*                                                                            */
/*   general_utils.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_messages(char *type)
{
	if (ft_strcmp(type, "ERROR_OPEN_FILE") == 0)
	{
		perror("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strcmp(type, "ERROR_FORK") == 0)
	{
		perror ("Error: Unable to fork\n");
		exit (EXIT_FAILURE);
	}
	else if (ft_strcmp(type, "BASH_MANY_ARGUMENTS") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return ;
	}
	else if (ft_strcmp(type, "BASH_NUMERIC_ARGS\n") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		return ;
	}
}