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

int	builtins_no_output(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return(1);
	return (-1);
}

int	builtins_with_output(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (-1);
}

int	exec_builtin(t_env *env_vars, t_main *main)
{
	if (ft_strcmp(main->cmd, "cd") == 0)
		return (env_vars->status = cd_builtin(env_vars, main->args[0]));
	else if (ft_strcmp(main->cmd, "pwd") == 0)
		return (env_vars->status = pwd_builtin());
	else if (ft_strcmp(main->cmd, "env") == 0)
		return (env_vars->status = env_builtin(env_vars));
	else if (ft_strcmp(main->cmd, "unset") == 0)
		return (env_vars->status = unset_builtin(env_vars, main->args[0]));
	else if (ft_strcmp(main->cmd, "export") == 0)
		return (env_vars->status = export_builtin(env_vars, main->args[0]));
	else if (ft_strcmp(main->cmd, "echo") == 0)
		return (env_vars->status = echo_builtin(main, env_vars));
	else if (ft_strcmp(main->cmd, "exit") == 0)
	{
		return (env_vars->status = exit_builtin(main));
		exit(env_vars->status);
	}
	return (-1);
}

int	exit_builtin(t_main *main)
{
	int	status;

	status = 0;
	 if (main->flags != NULL)
		status = ft_atoi(main->flags);
	else if (!main->args[0])
		exit(status);
	else if (main->args[1] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '-' && ft_isdigit(main->args[0][1])))
		status = ft_atoi(main->args[0]);
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '+' && ft_isdigit(main->args[0][1])))
		status = ft_atoi(main->args[0]);
	else
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	exit(status);
}
