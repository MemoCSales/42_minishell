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

void	cleanup_args(char **args)
{
	if (args)
	{
		cleanup_env_var(&args);
	}
}

void	clean_parse(char **ph, char **commands, char *line)
{
	if (ph)
		cleanup_env_var(&ph);
	if (commands)
		cleanup_env_var(&commands);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

void	process_args_and_update_struct(t_main *parsed_struct, \
		char **commands, int index, char **ph_strings)
{
	char	**args;
	int		num_commands;
	char	*command;

	num_commands = count_elements(commands);
	command = commands[index];
	args = ft_split(command, ' ');
	handle_redirections(parsed_struct, args, index);
	if (args[0] == NULL)
	{
		cleanup_args(args);
		return ;
	}
	check_flags(&parsed_struct[index], args);
	create_pipe(&parsed_struct[index], index, num_commands);
	free(parsed_struct[index].cmd);
	parsed_struct[index].cmd = malloc(ft_strlen(args[0]) + 1);
	check_malloc(parsed_struct[index].cmd);
	ft_strlcpy(parsed_struct[index].cmd, args[0], ft_strlen(args[0]) + 1);
	reverse_placeholders_in_struct(&parsed_struct[index], &ph_strings);
	cleanup_args(args);
}

t_main	*parse_line(char *line, t_env *env_var)
{
	t_main		*parsed_struct;
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
		process_args_and_update_struct(parsed_struct, commands, i, ph_strings);
		i++;
	}
	parsed_struct[count_elements(commands)].cmd = NULL;
	clean_parse(ph_strings, commands, line);
	return (parsed_struct);
}
// while (i < count_elements(commands))
// {
// 	old_command = commands[i];
// 	commands[i] = process_command_string(old_command);
// 	free(old_command);
// 	// args = ft_split(commands[i], ' ');
// 	// handle_redirections(parsed_struct, args, i);
// 	// if (args[0] == NULL)
// 	// 	break ;
// 	// check_flags(&parsed_struct[i], args);
// 	// create_pipe(&parsed_struct[i], i, count_elements(commands));
// 	// free(parsed_struct[i].cmd);
// 	// parsed_struct[i].cmd = malloc(ft_strlen(args[0]) + 1);
// 	// check_malloc(parsed_struct[i].cmd);
// 	// ft_strlcpy(parsed_struct[i].cmd, args[0], ft_strlen(args[0]) + 1);
// 	// reverse_placeholders_in_struct(&parsed_struct[i], &ph_strings);
// 	process_args_and_update_struct(parsed_struct, commands, i, ph_strings);
// 	// if (args)
// 	// 	cleanup_env_var(&args);
// 	i++;
// }

// t_main	*parse_line(char *line, t_env *env_var)
// {
// 	t_main		*parsed_struct;
// 	char		**args;
// 	char		**commands;
// 	char		*old_command;
// 	char		**ph_strings;
// 	int			i;

// 	i = 0;
// 	line = prepare_line(line, &ph_strings, env_var);
// 	if (line[0] == '\0')
// 		return (NULL);
// 	commands = ft_split(line, '|');
// 	parsed_struct = initialize_main(NULL, count_elements(commands));
// 	while (i < count_elements(commands))
// 	{
// 		old_command = commands[i];
// 		commands[i] = process_command_string(old_command);
// 		free(old_command);

// 		args = ft_split(commands[i], ' ');
// 		handle_redirections(parsed_struct, args, i);
// 		if (args[0] == NULL)
// 			break ;
// 		check_flags(&parsed_struct[i], args);
// 		create_pipe(&parsed_struct[i], i, count_elements(commands));
// 		free(parsed_struct[i].cmd);
// 		parsed_struct[i].cmd = malloc(ft_strlen(args[0]) + 1);
// 		check_malloc(parsed_struct[i].cmd);
// 		ft_strlcpy(parsed_struct[i].cmd, args[0], ft_strlen(args[0]) + 1);
// 		reverse_placeholders_in_struct(&parsed_struct[i], &ph_strings);
// 		if (args)
// 			cleanup_env_var(&args);
// 		i++;

// 	}
// 	parsed_struct[count_elements(commands)].cmd = NULL;
// 	clean_parse(ph_strings, commands, line);
// 	return (parsed_struct);
// }

t_main	*initialize_main(t_main *main_var, int num_commands)
{
	int	i;

	i = 0;
	free(main_var);
	main_var = malloc((num_commands + 1) * sizeof(t_main));
	check_malloc(main_var);
	while (i < num_commands)
	{
		main_var[i].cmd = NULL;
		main_var[i].flags = NULL;
		main_var[i].args = NULL;
		main_var[i].input_file = NULL;
		main_var[i].output_file = NULL;
		main_var[i].heredoc = NULL;
		main_var[i].extra = NULL;
		main_var[i].current_dir = getcwd(NULL, 0);
		main_var[i].syntaxflag = 0;
		main_var[i].fd[0] = -1;
		main_var[i].fd[1] = -1;
		i++;
	}
	return (main_var);
}
