/* ************************************************************************** */
/*                                                                            */
/*   general_utils.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_messages(char *type)
{
	if (ft_strcmp(type, "ERROR_OPEN_FILE") == 0)
	{
		perror("Error opening file\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strcmp(type, "ERROR_FORK") == 0)
	{
		perror("Error: Unable to fork\n");
		exit(EXIT_FAILURE);
	}
	else if (ft_strcmp(type, "BASH_MANY_ARGUMENTS") == 0)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("ψΨ: exit: too many arguments\n", 2);
		return ;
	}
	else if (ft_strcmp(type, "BASH_NUMERIC_ARGS") == 0)
	{
		ft_putstr_fd("ψΨ: exit: numeric argument required\n", 2);
		return ;
	}
}

void	print_open_fds(void)
{
	long	open_max;
	int		i;

	open_max = sysconf(_SC_OPEN_MAX);
	i = 0;
	while (i < open_max)
	{
		if (fcntl(i, F_GETFD) != -1 || errno != EBADF)
			printf("File descriptor %d is open\n", i);
		i++;
	}
}

void	ft_strcpy_memo(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

/* This function will handle the updating of the environment variables.*/
void	update_env(t_env *env_vars, char *prev_dir, t_main *main)
{
	if (prev_dir != NULL)
		update_env_var(env_vars, "OLDPWD", prev_dir);
	if (main->current_dir != NULL)
		update_env_var(env_vars, "PWD", main->current_dir);
}

void	update_env_var(t_env *env, char *var_name, char *new_value)
{
	char	*new_var;

	new_var = create_new_var(var_name, new_value);
	if (new_var != NULL)
		find_and_replace_var(env, var_name, new_var);
}
