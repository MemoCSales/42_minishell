/* ************************************************************************** */
/*                                                                            */
/*   buildins.c                 ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
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
		// return (env_vars->status = exit_builtin(main));
		env_vars->status = exit_builtin(main);
		// check_env(env_vars);
		// printf("exit\n");
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
	{
		printf("exit\n");
		exit(status);
	}
	else if (main->args[1] != NULL)
	{
		error_messages("BASH_MANY_ARGUMENTS");
		return (1);
	}
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '-'
		&& ft_isdigit(main->args[0][1])))
		status = ft_atoi(main->args[0]);
	else if (ft_isdigit(main->args[0][0]) || (main->args[0][0] == '+'
		&& ft_isdigit(main->args[0][1])))
		status = ft_atoi(main->args[0]);
	else
	{
		error_messages("BASH_NUMERIC_ARGS");
		return (2);
	}
	printf("exit\n");
	exit(status);
}
