/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/06 22:53:18 by demacinema       ###   ########.fr       */
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
	char	*tmp;
	int		num_commands;

	while (1) //prints a prompt and retrieves from what it reads
	{
		// line = readline("\001" LIGHT_RED "\002" "ψΨ:" "\001" DEFAULT "\002");
		line = readline("\033[1;31mψΨ:\033[0m");
		tmp = ft_strdup(line);
		free(line);
		line = ft_strdup(tmp);
		
		// if (ft_strlen(line) > 0)
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
			print_open_fds();
			printf("\n");
			env_var.status = execute_command(&env_var, main_var);
			print_open_fds();
		// 	else
		// 		exec_buildin(&env_var, main_var);
		// }
		// free_main(main_var); // This does not goes here
		// printf("MAIN EXIT CODE: %d\n", env_var.status);
		// free(main_var);
		free(line);
	}
}
