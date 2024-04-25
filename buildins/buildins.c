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

int	buildins(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return(1);
	return (-1);
}

void	exec_buildin(t_env *env_vars, t_main *main)
{
	if (ft_strcmp(main->cmd, "cd") == 0)
		cd_buildin(main->args[0]);
	else if (ft_strcmp(main->cmd, "pwd") == 0)
		pwd_buildin();
	else if (ft_strcmp(main->cmd, "env") == 0)
		env_buildin(env_vars);
	else if (ft_strcmp(main->cmd, "unset") == 0)
		unset_buildin(env_vars, main->args[0]);
	else if (ft_strcmp(main->cmd, "export") == 0)
		export_buildin(env_vars, main->args[0]);
	else if (ft_strcmp(main->cmd, "echo") == 0)
		echo_buildin(main, env_vars);
	else if (ft_strcmp(main->cmd, "exit") == 0)
		exit_buildin(main, env_vars);
}

void	exit_buildin(t_main *main, t_env *env_vars)
{
	env_vars->status = 0;
	if (main->flags != NULL)
		env_vars->status = ft_atoi(main->flags);
	else if (main->args[1] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		env_vars->status = 1;
		return ;
	}
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '-' && ft_isdigit(main->args[0][1])))
		env_vars->status = ft_atoi(main->args[0]);
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '+' && ft_isdigit(main->args[0][1])))
		env_vars->status = ft_atoi(main->args[0]);
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		env_vars->status = 2;
		return ;
	}
	exit(env_vars->status);
}
