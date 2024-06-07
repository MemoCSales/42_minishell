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

int	check_redir(t_main *main, char **args, int j)
{
	if (ft_strcmp(args[j], ">>") == 0
		|| ft_strcmp(args[j], "<<") == 0
		|| ft_strcmp(args[j], "<") == 0
		|| ft_strcmp(args[j], ">") == 0)
	{
		if (args[j + 1] == NULL)
		{
			ft_putstr_fd \
			("ψΨ: syntax error near unexpected token `newline'\n", 2);
			main->syntaxflag = 1;
			return (0);
		}
		else if (!(args [j + 2]))
		{
			redir_no_arg(args, j);
			return (1);
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
		before_var_len = *j - ft_strlen(var_name) - 1;
		after_var_len = ft_strlen(prepared + *j);
		new_prepared = malloc(before_var_len + \
		ft_strlen(var_value) + after_var_len + 1);
		check_malloc(new_prepared);
		ft_strncpy(new_prepared, prepared, before_var_len);
		new_prepared[before_var_len] = '\0';
		ft_strcpy(new_prepared + before_var_len, var_value);
		ft_strcpy(new_prepared + before_var_len + \
		ft_strlen(var_value), prepared + *j);
		free(prepared);
		prepared = new_prepared;
		*j = before_var_len + strlen(var_value);
	}
	return (prepared);
}
