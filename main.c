/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_main	*main_var;
	t_env	env_var;
	int		num_commands;

	(void)argc;
	(void)argv;
	init_env(&env_var, env); // This function initialize the env_vars
	while (1)               
		// first while loop that prints a prompt and retrieves from what it reads
	{
		line = readline("\001\033[0;91m\002mini\001\033[1;91m\002ℍ\001\033[0;91m\002ΞLL>> \001\033[0m\002");
		if (ft_strlen(line) > 0)
			add_history(line);
		main_var = parse_line(line);
		num_commands = 0;
		while (main_var[num_commands].cmd)
			num_commands++;
		print_struct(main_var); // printing parsing result
		printf("\n");
		// exit(0);
		if (num_commands >= 1)
		{
			if (buildins(main_var->cmd) == -1)
				execute_command(&env_var, main_var);
			else
				exec_buildin(&env_var, main_var);
		}
		// free_main(main_var); // This does not goes here
		free(line);
	}
	check_env(&env_var);
		// In this function it checks env_vars and frees the memory. Need to check if its needed
	return (0);
}
