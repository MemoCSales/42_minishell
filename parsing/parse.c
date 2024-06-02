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
	char		*old_command;
	char		**ph_strings;
	int			i;

	i = 0;
	line = prepare_line(line, &ph_strings, env_var);
	if (line[0] == '\0')
		return (NULL);
	commands = ft_split(line, '|');
	parsed_struct = initialize_main(NULL, count_elements(commands));
	while (i < count_elements(commands))
	{
		old_command = commands[i];
		commands[i] = process_command_string(old_command);
		free(old_command);
		args = ft_split(commands[i], ' ');
		handle_redirections(parsed_struct, args, i);
		check_flags(&parsed_struct[i], args);
		create_pipe(&parsed_struct[i], i, count_elements(commands));
	free(parsed_struct[i].cmd);
	parsed_struct[i].cmd = malloc(ft_strlen(args[0]) + 1);
	check_malloc(parsed_struct[i].cmd);
	ft_strlcpy(parsed_struct[i].cmd, args[0], ft_strlen(args[0]) + 1); //SO I AM ABLE TO FREE ARGS
		// parsed_struct[i].cmd = args[0];
		// ft_strcpy(parsed_struct[i].cmd, args[0]);//NA DUVIDA AQUI. TEM Q LIBERAR TUDO DO ARGS, MAS E ASSIM Q COPIA PRA LIBERAR DEPOIS?
		reverse_placeholders_in_struct(&parsed_struct[i], &ph_strings);

	if (args)
		cleanup_env_var(&args);

		i++;
	}
	parsed_struct[count_elements(commands)].cmd = NULL;

// printf("ARGS: %p - %s\n", args, args[0]);
// print_args(args);
// 	if (args)
// 		cleanup_env_var(&args);

printf("PH_STRINGS: %p - %s\n", ph_strings, ph_strings[0]);
print_args(ph_strings);
	if (ph_strings)
		cleanup_env_var(&ph_strings);

printf("COMMANDS: %p - %s\n", commands, commands[0]);
print_args(commands);
	if (commands)
		cleanup_env_var(&commands);

printf("LINE: %p - %s\n", line, line);
	if (line)
	{
printf("1freed line: %p - \"%s\"\n", line, line);
		free(line);
		line = NULL;
printf("2freed line: %p - \"%s\"\n", line, line);
	}
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
		// printf("MEMORITES:%p - %s\n", main_var[i].args, main_var[i].args[0]);
		check_malloc(main_var[i].args);
		// main_var[i].args[0] = NULL;
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
