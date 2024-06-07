/* ************************************************************************** */
/*                                                                            */
/*   cd.c                       ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function will handle the actual changing of
the directory and updating of the main->current_dir variable.*/
int	change_directory(t_main *main, char *path)
{
	int		status;
	char	*home;

	status = chdir(path);
	if (status == 0)
	{
		free(main->current_dir);
		main->current_dir = getcwd(NULL, 0);
		if (main->current_dir == NULL)
		{
			home = getenv("HOME");
			chdir(home);
			main->current_dir = ft_strdup(home);
		}
	}
	return (status);
}

char	*get_prev_dir(t_main *main, int *flag_free)
{
	char	*prev_dir;

	if (main->current_dir != NULL)
	{
		prev_dir = ft_strdup(main->current_dir);
		*flag_free = 1;
	}
	else
		prev_dir = getenv("HOME");
	return (prev_dir);
}

char	*handle_path(t_main *main, char *path, char *prev_dir, int *flag_free)
{
	path = get_path(main, path);
	if (path == NULL && *flag_free)
	{
		free(prev_dir);
		prev_dir = NULL;
	}
	return (path);
}

int	cd_builtin(t_env *env_vars, char *path, t_main *main)
{
	int		status;
	int		flag_free;
	char	*prev_dir;

	flag_free = 0;
	prev_dir = get_prev_dir(main, &flag_free);
	path = handle_path(main, path, prev_dir, &flag_free);
	if (path == NULL)
		return (1);
	status = change_directory(main, path);
	if (status == 0)
		update_env(env_vars, prev_dir, main);
	else
		cd_error_check(path);
	if (flag_free)
	{
		free(prev_dir);
		prev_dir = NULL;
	}
	if (status == 0)
		return (0);
	else
		return (1);
}

void	cd_error_check(char *path)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("cd: Permission denied: ", STDERR_FILENO);
		printf("%s\n", path);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("ψΨ: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
}
