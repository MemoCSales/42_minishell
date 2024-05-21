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

char	*read_command()
{
	return (readline("\033[1;31mψΨ:\033[0m"));
}

t_main	*parse_command(char *line)
{
	t_main	*main_var;

	main_var = parse_line(line);
	if (!main_var)
	{
		printf("Error parsing line\n");
		free(line);
	}
	return (main_var);
}
int	execute_commands(t_env *env_var, t_main *main_var)
{
	// int	num_commands;
	int	status;

	main_var->num_cmds = 0;
	while (main_var[main_var->num_cmds].cmd)
		main_var->num_cmds++;
	status = execute_command(env_var, main_var);
	// status = execute_command2(env_var, main_var);
	free_parsed_struct(main_var, main_var->num_cmds);
	return (status);
}

void	main_loop(t_env env_var, t_main *main_var)
{
	char	*line;

	line = NULL;
	setup_signals();
	while (1)
	{
		line = read_command();
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (line && *line)
		{
			add_history(line);
			main_var = parse_command(line);
			if (main_var)
				env_var.status = execute_commands(&env_var, main_var);
		}
		free(line);
		line = NULL;
	}
}
