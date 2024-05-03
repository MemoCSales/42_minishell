/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_open_fds(void)
{
	long	open_max = sysconf(_SC_OPEN_MAX);

	for(int i = 0; i < open_max; i++)
	{
		if (fcntl(i, F_GETFD) != -1 || errno!= EBADF)
			printf("File descriptor %d is open\n", i);
	}
}

void    main_loop(t_env env_var, t_main *main_var)
{
	char	*line;
	int		num_commands;
	while (1)			// first while loop that prints a prompt and retrieves from what it reads
	{
		line = readline(LIGHT_RED"ψΨ: "DEFAULT"");
		if (ft_strlen(line) > 0)
			add_history(line);
		// main_var = initialize_main(main_var, 0);
		main_var = parse_line(line);
		num_commands = 0;
		while (main_var[num_commands].cmd)
			num_commands++;
// print_struct(main_var, num_commands); // printing parsing result
// printf("\n");
// exit(0);
		// if (num_commands >= 1)
		// {
			// if (buildins(main_var->cmd) == -1)
			// print_open_fds();
				env_var.status = execute_command(&env_var, main_var);
			// print_open_fds();
		// 	else
		// 		exec_buildin(&env_var, main_var);
		// }
		// free_main(main_var); // This does not goes here

		free(line);
	}
}
