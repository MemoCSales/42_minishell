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
int is_fd_closed(int fd) {
    int flags = fcntl(fd, F_GETFD);
    return flags == -1; // If fcntl() returns -1, the file descriptor is closed
}


void close_all_pipes(t_main *main, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		if (main[i].fd[0] != -1)
		{
			close(main[i].fd[0]);
			// main[i].fd[0] = -1;
		}
		if (main[i].fd[1] != -1)
		{
			close(main[i].fd[1]);
			// main[i].fd[1] = -1;
		}
		i++;
	}	
}

void	main_loop(t_env env_var, t_main *main_var)
{
	char	*line;
	// char	*tmp;
	int		num_commands;

	while (1) //prints a prompt and retrieves from what it reads
	{
		// line = readline("\001" LIGHT_RED "\002" "ψΨ:" "\001" DEFAULT "\002");
		line = readline("\033[1;31mψΨ:\033[0m");
		// tmp = ft_strdup_minishell(line);
		// free(line);
		// line = ft_strdup_minishell(tmp);
		
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
			// printf("\n");
		env_var.status = execute_command(&env_var, main_var);
		// env_var.status = execute_command2(&env_var, main_var);
		// printf("\n");
		// close_all_pipes(main_var, num_commands);
			// exit(0);
			// print_open_fds();
		// 	else
		// 		exec_buildin(&env_var, main_var);
		// }
		// free_main(main_var); // This does not goes here
		// printf("MAIN EXIT CODE: %d\n", env_var.status);
		// free(main_var);
		free(line);
		line = NULL;
	}
}
