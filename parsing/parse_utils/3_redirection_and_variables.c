/* ************************************************************************** */
/*                                                                            */
/*   3_redirection_and_variables.c     ψΨ MiniℍΞLL Ψψ     :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int file_exists(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		// File doesn't exist
		return (0);
	} else
	{
		// File exists
		close(fd); // Close the file descriptor
		return (1);
	}
}

int redir_no_arg(char **args, int j)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(args[j], "<") == 0)
	{
		// printf("< and no arg\n");
		if (file_exists(args[j + 1]) == 1)
			return (0);
		else
		{
			printf("Error: No such file or directory: %s\n", args[j + 1]);
			// return (0);
		}
	}
	else if ((ft_strcmp(args[j], ">") == 0) || ft_strcmp(args[j], ">>") == 0)
	{
		if (file_exists(args[j + 1]) == 1)
			return (0);
		else
		{
			fd = open(args[j + 1], O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0644);
			if (fd < 0)
				error_messages("ERROR_OPEN_FILE");
			close(fd);
		}
	}
	return (0);
}

// int fd = open("myfile.txt", O_CREAT | O_EXCL, 0644);
// if (fd < 0) {
//     // File exists
// } else {
//     // File doesn't exist, and has been created
//     close(fd); // Close the file descriptor
// }

int	check_redir(char **args, int j)
{
	if (ft_strcmp(args[j], ">>") == 0
		|| ft_strcmp(args[j], "<<") == 0
		|| ft_strcmp(args[j], "<") == 0
		|| ft_strcmp(args[j], ">") == 0)
	{
		if (!(args [j + 2]))//AND '<', AND NO input.txt
		{
			redir_no_arg(args, j);
			// printf("Error: No such file or directory: %s\n", args[j + 1]);
			// return (1);
		//IF (!(!(args [j + 2]))//AND '<', AND YES input.txt
			//REPROMPT
		//
		//IF (!(!(args [j + 2]))//AND '>', AND NO output.txt
			//CREATE FILE AND REPROMPT
		//IF (!(!(args [j + 2]))//AND '>', AND YES output.txt
			//REPROMPT
		//IF (!(!(args [j + 2]))//AND '<<'
			//HEREDOC //return(1);
		//IF (!(!(args [j + 2]))//AND '>>' AND YES input.txt
			//REPROMPT
		//IF (!(!(args [j + 2]))//AND '>>' AND NO input.txt
			//REPROMPT
		}
		return (1);
	}
	else
	{
		return (0);
	}
}

void	redirection(t_main *parsed_struct, char **args, int i, int j)
{
	char	*delimiter;
	char	*heredoc;

	heredoc = NULL;
	if (ft_strcmp(args[j], ">>") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
		parsed_struct[i].extra = ft_strdup(args[j]);
	}
	else if (ft_strcmp(args[j], "<<") == 0 && args[j + 1])
	{
		delimiter = args[j + 1];
		heredoc = read_heredoc(delimiter);
		parsed_struct[i].heredoc = heredoc;
	}
	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
	{
		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
	}
	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
	}
	remove_args(args, j, 2);
}

void	handle_variables_ph(char *line, char **prepared, int *i, int *j)
{
	char	var_name[1024];

	if (line[*i] == '$' && (*i == 0 || line[*i - 1] != '\\'))
	{
		(*i)++;
		get_var_name(line, i, var_name);
		if (*prepared != NULL)
			*prepared = replace_var_value(var_name, *prepared, j);
	}
}

void	get_var_name(char *line, int *i, char *var_name)
{
	int	j;

	j = 0;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		var_name[j++] = line[*i];
		(*i)++;
	}
	var_name[j] = '\0';
}

char	*replace_var_value(char *var_name, char *prepared, int *j)
{
	char	*var_value;
	char	*new_prepared;
	int		before_var_len;
	int		after_var_len;

	var_value = getenv(var_name);
	if (var_value != NULL && *j >= (int)(strlen(var_name) + 1)
		&& prepared != NULL)
	{
		before_var_len = *j - strlen(var_name) - 1;
		after_var_len = strlen(prepared + *j);
		new_prepared = malloc(before_var_len + \
		strlen(var_value) + after_var_len + 1);
		check_malloc(new_prepared);
		strncpy(new_prepared, prepared, before_var_len);
		new_prepared[before_var_len] = '\0';
		strcpy(new_prepared + before_var_len, var_value);
		strcpy(new_prepared + before_var_len + \
		strlen(var_value), prepared + *j);
		free(prepared);
		prepared = new_prepared;
		*j = before_var_len + strlen(var_value);
	}
	return (prepared);
}
