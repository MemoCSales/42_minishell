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

#include "minishell.h"

int	buildins(char **cmd)
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
	// check env, unset, exit
	// else if (ft_strcmp(cmd[0], "env") == 0)
	// {
	// 	env_buildin();
	// 	return(0);
	// }
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// {
	// 	unset_buildin(cmd[1]);
	// 	return (0);
	// }
	else if (ft_strcmp(cmd[0], "exit") == 0)
		exit(0);
	return (-1);
}

void	cd_buildin(char *path)
{
	int		status;
	char	*home;

	errno = 0;
	home = getenv("HOME");
	errno = 0;
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
		{
			ft_putstr_fd("cd: HOME environment variable not set\n",
				STDERR_FILENO);
		}
		path = home;
	}
	status = chdir(path);
	if (status == 0)
		printf("cd: Directory changed to %s\n", path);
	else
	{
		if (errno == EACCES)
		{
			ft_putstr_fd("cd: Permission denied: ", STDERR_FILENO);
			printf("%s\n", path);
		}
		else if (errno == ENOENT)
		{
			ft_putstr_fd("cd: No such file of directory: ", STDERR_FILENO);
			printf("%s\n", path);
		}
	}
}

void	pwd_buildin(void)
{
	char	cwd[MAX_CMD_LEN];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		ft_putstr_fd("pwd: error retrieving current directory", STDERR_FILENO);
}

//env buildin
// void env_buildin()
// {
// }
// First create the env buildin
// void	unset_buildin(char *variable)
// {
// 	if (variable == NULL)
// 	{
// 		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
// 		return ;
// 	}

// }
