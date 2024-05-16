/* ************************************************************************** */
/*                                                                            */
/*   pwd.c                      ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_builtin(t_main *main)
{
	if (main->current_dir != NULL)
	{
		printf("%s\n", main->current_dir);
		return (0);
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", STDERR_FILENO);
		return (1);
	}
}
