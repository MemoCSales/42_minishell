/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:37:46 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/04/02 13:37:47 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	buildins(t_env *env_vars, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		cd_buildin(cmd[1]);
		return (0);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		pwd_buildin();
		return (0);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		env_buildin(env_vars);
		return(0);
	}
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// {
	// 	unset_buildin(env_vars, cmd[1]);
	// 	return (0);
	// }
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit(0);
	return (-1);
}

// void	unset_buildin(t_env *env_vars, char *variable)
// {
// 	if (variable == NULL)
// 	{
// 		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
// 		return ;
// 	}

// }
