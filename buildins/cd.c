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

//FIX CD BUILDING
// IS NOT GOING BACK TO THE PREVIOUS FOLDER
void cd_buildin(char *path)
{
	int 	status;
	char 	*home;
	char	*olddir;
	static char *prev_dir;

	errno = 0;
	home = getenv("HOME");
	olddir = getenv("OLDPWD");
	prev_dir = NULL;
	if (path == NULL || *path == '\0')
	{
		if (home == NULL)
			ft_putstr_fd("cd: HOME environment variable not set\n", STDERR_FILENO);
		path = home;
	}
	else if (strcmp(path, "..") == 0)
	{
		if (olddir != NULL)
		{
			path = olddir;
			printf("new path to old directory\n");
		}
		else
			path = "..";
	}
	if (prev_dir != NULL)
		free(prev_dir);
	prev_dir = getcwd(NULL, 0); // Save current directory
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
			ft_putstr_fd("cd: No such file or directory: ", STDERR_FILENO);
			printf("%s\n", path);
		}
	}
}
