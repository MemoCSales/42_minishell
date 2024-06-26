/* ************************************************************************** */
/*                                                                            */
/*   builtins.c                 ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
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
		return (1);
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
		return (env_vars->status = cd_builtin(env_vars, main->args[0], main));
	else if (ft_strcmp(main->cmd, "pwd") == 0)
		return (env_vars->status = pwd_builtin(main));
	else if (ft_strcmp(main->cmd, "env") == 0)
		return (env_vars->status = env_builtin(env_vars));
	else if (ft_strcmp(main->cmd, "unset") == 0)
		return (env_vars->status = unset_builtin(env_vars, main->args[0]));
	else if (ft_strcmp(main->cmd, "export") == 0)
		return (env_vars->status = export_builtin(env_vars, main,
				main->args[0]));
	else if (ft_strcmp(main->cmd, "echo") == 0)
		return (env_vars->status = echo_builtin(main));
	else if (ft_strcmp(main->cmd, "exit") == 0)
	{
		env_vars->status = exit_builtin(main);
		exit(env_vars->status);
	}
	return (-1);
}
