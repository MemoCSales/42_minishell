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

char	*read_command(void)
{
	return (readline("\033[1;31mψΨ\033[0m "));
}

t_main	*parse_command(char *line, t_env *env_var)
{
	t_main	*main_var;

	main_var = parse_line(line, env_var);
	if (!main_var)
	{
		printf("Error parsing line\n");
	}
	return (main_var);
}

int	execute_commands(t_env *env_var, t_main *main_var)
{
	int	num_commands;
	int	status;

	num_commands = 0;
	while (main_var[num_commands].cmd)
		num_commands++;
	status = execute_command(env_var, main_var);
	free_parsed_struct(main_var, num_commands);
	return (status);
}

void	main_loop(t_env env_var, t_main *main_var)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = read_command();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line && *line)
		{
			add_history(line);
			main_var = parse_command(line, &env_var);
			if (main_var)
			{
				env_var.status = execute_commands(&env_var, main_var);
			}
		}
		free(line);
		line = NULL;
	}
}
