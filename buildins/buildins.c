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

int	buildins(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit(0);
	return (-1);
}

void	exec_buildin(t_env *env_vars, t_main *main)
{
	if (ft_strcmp(main->args[0], "cd") == 0)
		cd_buildin(main->args[1]);
	else if (ft_strcmp(main->args[0], "pwd") == 0)
		pwd_buildin();
	else if (ft_strcmp(main->args[0], "env") == 0)
		env_buildin(env_vars);
	else if (ft_strcmp(main->args[0], "unset") == 0)
		unset_buildin(env_vars, main->args[1]);
	else if (ft_strcmp(main->args[0], "export") == 0)
		export_buildin(env_vars, main->args[1]);
	else if (ft_strcmp(main->args[0], "echo") == 0)
		echo_buildin(main->args);
	else if (ft_strcmp(main->args[0], "exit") == 0)
		exit(0);
}