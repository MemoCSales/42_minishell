/* ************************************************************************** */
/*                                                                            */
/*   minishell.c                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	main_loop(t_env env_var, t_main *main_var)
{
	char	*line;
	int		num_commands;

	line = NULL;
	while (1)
	{
		line = readline("\033[1;31mψΨ:\033[0m");
		if (!line)
			printf("Error: readline\n");
		if (ft_strlen(line) > 0)
			add_history(line);
		main_var = parse_line(line);
		if (!main_var)
		{
			printf("Error parsing line\n");
			free(line);
			continue ;
		}
		num_commands = 0;
		while (main_var[num_commands].cmd)
			num_commands++;
		env_var.status = execute_command(&env_var, main_var);
		g_status = env_var.status;//ADDED FOR PARSING
		free_parsed_struct(main_var, num_commands);
		free(line);
	}
}
