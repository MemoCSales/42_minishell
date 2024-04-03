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

#include "minishell.h"

int	buildins(char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		cd_buildin(cmd[1]);
		return (0);
	}
	return (-1);
}

void	cd_buildin(char *path)
{
	int	status;
	char	*home;

	errno = 0;
	home = getenv("HOME");
	errno = 0;
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
			ft_putstr_fd("cd: HOME environment variable not set\n", STDERR_FILENO);
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
