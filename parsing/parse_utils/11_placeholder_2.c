/* ************************************************************************** */
/*                                                                            */
/*   11_placeholder_2.c             ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	placeholder(char *line, char ***ph_strings)
{
	int	num_strings;

	*ph_strings = extract_strings(line, &num_strings);
	if (*ph_strings)
		replace_with_placeholder(line);
}

// WITH PRINTS
// void	placeholder(char *line, char ***ph_strings)
// {
// 	int	i;
// 	int	num_strings;

// 	*ph_strings = extract_strings(line, &num_strings);
// 	if (*ph_strings)
// 	{
// 		replace_with_placeholder(line);
// 		printf("Modified line: %s\n", line);
// 		printf("Strings between quotes:\n");
// 		i = 0;
// 		while (i < num_strings)
// 		{
// 			printf("%d: %s\n", i + 1, (*ph_strings)[i]);
// 			i++;
// 		}
// 	}
// }

void	replace_single_placeholder(char **command,
			char *placeholder, char *replacement)
{
	char	*new_command;

	new_command = ft_strswap(*command, placeholder, replacement);
	free(*command);
	*command = new_command;
}

void	replace_placeholder_sub(char **str,
	char *placeholder, char *replacement)
{
	char	*pos;
	char	*new_str;

	if (*str != NULL && placeholder != NULL)
	{
		pos = strstr(*str, placeholder);
		if (pos != NULL)
		{
			new_str = malloc(strlen(*str)
					- strlen(placeholder) + strlen(replacement) + 1);
			strncpy(new_str, *str, pos - *str);
			new_str[pos - *str] = '\0';
			strcat(new_str, replacement);
			strcat(new_str, pos + strlen(placeholder));
			free(*str);
			*str = new_str;
		}
	}
}

void	reverse_placeholders(char **str, char ***ph_strings)
{
	char	*placeholder;
	char	*replacement;
	int		i;

	i = 0;
	while ((*ph_strings)[i] != NULL)
	{
		placeholder = ft_strjoin("Ψ(", ft_itoa(i + 1));
		placeholder = ft_strjoin(placeholder, ")");
		replacement = (*ph_strings)[i];
		replace_placeholder_sub(str, placeholder, replacement);
		free(placeholder);
		i++;
	}
}

void	reverse_placeholders_in_struct(t_main *command, char ***ph_strings)
{
	int	j;

	j = 0;
	reverse_placeholders(&command->cmd, ph_strings);
	reverse_placeholders(&command->flags, ph_strings);
	reverse_placeholders(&command->input_file, ph_strings);
	reverse_placeholders(&command->output_file, ph_strings);
	reverse_placeholders(&command->heredoc, ph_strings);
	reverse_placeholders(&command->extra, ph_strings);
	while (command->args[j] != NULL)
	{
		reverse_placeholders(&command->args[j], ph_strings);
		j++;
	}
}

// void	replace_placeholders(char **command, char ***ph_strings)
// {
// 	char	*placeholder;
// 	char	*replacement;
// 	int		i;

// 	i = 0;
// 	while ((*ph_strings)[i] != NULL)
// 	{
// 		placeholder = ft_strjoin("Ψ(", ft_itoa(i + 1));
// 		placeholder = ft_strjoin(placeholder, ")");
// 		replacement = (*ph_strings)[i];
// 		replace_single_placeholder(command, placeholder, replacement);
// 		free(placeholder);
// 		i++;
// 	}
// }

// void reverse_placeholders(char **command, char ***ph_strings)
// {
//     char *placeholder;
//     char *original;
//     int i = 0;

//     while ((*ph_strings)[i] != NULL)
//     {
//         placeholder = ft_strjoin("Ψ(", ft_itoa(i + 1));
//         placeholder = ft_strjoin(placeholder, ")");
//         original = (*ph_strings)[i];
//         replace_single_placeholder(command, placeholder, original);
//         free(placeholder);
//         i++;
//     }
// }

// void replace_single_placeholder(char **command,
	// char *placeholder, char *replacement)
// {
//     char *new_command;

//     new_command = ft_strreplace(*command, placeholder, replacement);
//     free(*command);
//     *command = new_command;
// }

// void replace_placeholders(char **command, char ***ph_strings)
// {
//     char *placeholder;
//     char *replacement;
//     int i;

//     for (i = 0; (*ph_strings)[i] != NULL; i++)
//     {
//         placeholder = ft_strjoin("Ψ(", ft_itoa(i + 1));
//         placeholder = ft_strjoin(placeholder, ")");
//         replacement = (*ph_strings)[i];
//         replace_single_placeholder(command, placeholder, replacement);
//         free(placeholder);
//     }
// }

// int get_count_and_length(char *str, char *old, int *len_old, int *len_new)
// {
//     char *ins;
//     char *tmp;
//     int count;

//     if (!str || !old || !(*len_old = ft_strlen(old))
// 			|| !(*len_new = ft_strlen(old)))
//         return -1;
//     ins = str;
//     for (count = 0; (tmp = ft_strstr(ins, old)); ++count)
//         ins = tmp + *len_old;
//     return count;
// }

// char *replace_and_copy(char *str, char *old, char *new,
	// char *result, int count, int len_old, int len_new)
// {
//     char *tmp;
//     int len_front;

//     tmp = result;
//     for (; count > 0; count--)
//     {
//         char *ins = ft_strstr(str, old);
//         len_front = ins - str;
//         tmp = ft_strncpy(tmp, str, len_front) + len_front;
//         tmp = ft_strcpy(tmp, new) + len_new;
//         str += len_front + len_old;
//     }
//     ft_strcpy(tmp, str);
//     return result;
// }

// char *ft_strreplace(char *str, char *old, char *new)
// {
//     char *result;
//     int len_old, len_new, count;

//     count = get_count_and_length(str, old, &len_old, &len_new);
//     if (count == -1)
//         return NULL;
//     result = ft_strnew(ft_strlen(str) + (len_new - len_old) * count + 1);
//     if (!result)
//         return NULL;
//     return replace_and_copy(str, old, new, result, count, len_old, len_new);
// }

//PARSELINE ANTIGO (FUNCIONANDO)
// t_main	*parse_line(char *line)
// {
// 	t_main		*parsed_struct;
// 	char		**args;
// 	char		**commands;
// 	int			num_commands;
// 	int			i;

// 	i = 0;
// 	line = prepare_line(line);
// // printf("Modified line 2: %s\n", line);
// 	commands = ft_split(line, '|');
// 	num_commands = count_elements(commands);
// // print_args(commands);
// 	parsed_struct = NULL;

// 	parsed_struct = initialize_main(parsed_struct, num_commands);

// 	while (i < num_commands)
// 	{

// 		commands[i] = process_command_string(commands[i]);
// printf("OK\n");
// 		// args = ft_split_args(commands[i], ' ');
// 		args = ft_split(commands[i], ' ');
// printf("OK1\n");
// print_args(args);
// 		clean_quotes(args);
// printf("OK2\n");
// 		parsed_struct[i].cmd = args[0];
// printf("OK3\n");
// 		handle_redirections(parsed_struct, args, i);
// printf("OK4\n");
// 		check_flags(&parsed_struct[i], args);
// printf("OK5\n");
// 		create_pipe(&parsed_struct[i], i, num_commands);
// printf("OK6\n");
// 		i++;
// 	}
// 	parsed_struct[num_commands].cmd = NULL;
// 	//VOLTAR AQUI, OS PLACEHOLDERS
// 	i = 0;
// 	while (i < num_commands)
// 		print_struct(parsed_struct, i++);
// 	return (parsed_struct);
// }
