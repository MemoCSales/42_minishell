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

t_main	*parse_line(char *line, t_env *env_var)
{
	t_main		*parsed_struct;
	char		**args;
	char		**commands;
	char		**ph_strings;
	int			i;

	i = 0;
	line = prepare_line(line, &ph_strings, env_var);
	if (line[0] == '\0')
		return (NULL);
	commands = ft_split(line, '|');
	free(line);
	parsed_struct = initialize_main(NULL, count_elements(commands));
	while (i < count_elements(commands))
	{
		commands[i] = process_command_string(commands[i]);
		args = ft_split(commands[i], ' ');
		handle_redirections(parsed_struct, args, i);
		check_flags(&parsed_struct[i], args);
		create_pipe(&parsed_struct[i], i, count_elements(commands));
		parsed_struct[i].cmd = args[0];
		reverse_placeholders_in_struct(&parsed_struct[i], &ph_strings);
		i++;
	}
	parsed_struct[count_elements(commands)].cmd = NULL;
	cleanup_split(commands);
	return (parsed_struct);
}

t_main	*initialize_main(t_main *main_var, int num_commands)
{
	int	i;

	i = 0;
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	check_malloc(main_var);
	while (i < num_commands)
	{
		main_var[i].cmd = NULL;
		main_var[i].flags = NULL;
		main_var[i].args = malloc(sizeof(char *));
		check_malloc(main_var[i].args);
		main_var[i].args[0] = NULL;
		main_var[i].input_file = NULL;
		main_var[i].output_file = NULL;
		main_var[i].heredoc = NULL;
		main_var[i].extra = NULL;
		main_var[i].current_dir = getcwd(NULL, 0);
		main_var[i].fd[0] = -1;
		main_var[i].fd[1] = -1;
		i++;
	}
	return (main_var);
}

// PRINT STRUCTS
	// i = 0;
	// while (i < count_elements(commands))
	// {
	// 	print_struct(parsed_struct, i);
	// 	i++;
	// }

// BEFORE NORMETTIZATION
// t_main	*parse_line(char *line, t_env *env_var)
// {
// 	t_main		*parsed_struct;
// 	char		**args;
// 	char		**commands;
// 	char		**ph_strings;
// 	int			i;

// 	i = 0;
// 	// ph_strings = NULL;
// 	line = prepare_line(line, &ph_strings, env_var);
// 	if (line[0] == '\0')
// 		return (NULL);
// 	commands = ft_split(line, '|');
// 	// parsed_struct = NULL;
// 	// parsed_struct = initialize_main(parsed_struct, count_elements(commands));
// 	parsed_struct = initialize_main(NULL, count_elements(commands));
// 	while (i < count_elements(commands))
// 	{
// 		commands[i] = process_command_string(commands[i]);
// 		args = ft_split(commands[i], ' ');
// 		handle_redirections(parsed_struct, args, i);
// 		check_flags(&parsed_struct[i], args);
// 		create_pipe(&parsed_struct[i], i, count_elements(commands));
// 		parsed_struct[i].cmd = args[0];
// 		reverse_placeholders_in_struct(&parsed_struct[i], &ph_strings);
// 		i++;
// 	}
// 	parsed_struct[count_elements(commands)].cmd = NULL;
// 	return (parsed_struct);
// }
