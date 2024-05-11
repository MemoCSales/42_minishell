/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 20:59:34 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_main	*parse_line(char *line)
{
	t_main	*parsed_struct;
	char	**args;
	char	**commands;
	int		num_commands;
	int		i;

	i = 0;
	line = prepare_line(line);
	commands = ft_split(line, '|');
	num_commands = count_elements(commands);
	parsed_struct = NULL;
	parsed_struct = initialize_main(parsed_struct, num_commands);
	while (i < num_commands)
	{
		commands[i] = insert_spaces(commands[i]);
		args = ft_split(commands[i], ' ');
		clean_quotes(args);
		parsed_struct[i].cmd = args[0];
		handle_redirections(parsed_struct, args, i);
		check_flags(&parsed_struct[i], args);
		create_pipe(&parsed_struct[i], i, num_commands);
		i++;
	}
	parsed_struct[num_commands].cmd = NULL;
	return (parsed_struct);
}
