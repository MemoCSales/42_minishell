/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_4.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_quotes(char *line)
{
	int	i;
	int	in_single_quotes;
	int	in_double_quotes;
	int	result;

	result = 0;
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\'') && !in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			if (DEBUG)
			{
				printf("INSIDE SINGLE QUOTES [%c] [%d]\n",
					line[i], in_single_quotes);
			}
			i++;
			continue ;
		}
		if ((line[i] == '\'') && in_single_quotes)
		{
			in_single_quotes = !in_single_quotes;
			if (DEBUG)
			{
				printf("OUTSIDE SINGLE QUOTES [%c] [%d]\n",
					line[i], in_single_quotes);
			}
			i++;
			continue ;
		}
		if ((line[i] == '\"') && !in_double_quotes)
		{
			in_double_quotes = !in_double_quotes;
			if (DEBUG)
			{
				printf("INSIDE DOUBLE QUOTES [%c] [%d]\n",
					line[i], in_double_quotes);
			}
			i++;
			continue ;
		}
		if ((line[i] == '\"') && in_double_quotes && (line[i - 1] != '\\'))
		{
			in_double_quotes = !in_double_quotes;
			if (DEBUG)
			{
				printf("OUTSIDE DOUBLE QUOTES [%c] [%d]\n", line[i],
					in_double_quotes);
			}
			i++;
			continue ;
		}
		i++;
	}
	if (in_single_quotes)
		result = 1;
	else if (in_double_quotes)
		result = 2;
	return (result);
}

char	*get_last_exit_status(void)
{
	char	*status_str;
	int		status;
	pid_t	pid;

	pid = wait(&status);
	if (pid == -1)
	{
		status_str = ft_strdup("-1");
	}
	else if (WIFEXITED(status))
	{
		status_str = ft_itoa(WEXITSTATUS(status));
	}
	else
	{
		status_str = ft_strdup("Error");
	}
	return (status_str);
}

char	*ft_strswap(char *str, char *substr, char *replacement)
{
	char	*new_str;
	char	*temp;
	size_t	substr_len;
	size_t	replacement_len;

	temp = NULL;
	if (!str || !substr || !replacement)
		return (NULL);
	substr_len = ft_strlen(substr);
	replacement_len = ft_strlen(replacement);
	new_str = ft_strdup("");
	while (*str != '\0')
	{
		if (ft_strncmp(str, substr, substr_len) == 0)
		{
			temp = new_str;
			new_str = ft_strjoin(new_str, replacement);
			free(temp);
			str += substr_len;
		}
		else
		{
			temp = new_str;
			new_str = ft_strnjoin(new_str, str, 1);
			free(temp);
			str++;
		}
	}
	return (new_str);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + n + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (j < n)
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	free_parsed_struct(t_main *parsed_struct, int num_commands)
{
	int	i;

	i = 0;
	while ((parsed_struct) && (i < num_commands))
	{
		if (parsed_struct[i].cmd)
		{
			free(parsed_struct[i].cmd);
			parsed_struct[i].cmd = NULL;
		}
		if (parsed_struct[i].flags)
		{
			free(parsed_struct[i].flags);
			parsed_struct[i].flags = NULL;
		}
		if (parsed_struct[i].args)
		{
			free(parsed_struct[i].args);
			parsed_struct[i].args = NULL;
		}
		if (parsed_struct[i].input_file)
		{
			free(parsed_struct[i].input_file);
			parsed_struct[i].input_file = NULL;
		}
		if (parsed_struct[i].output_file)
		{
			free(parsed_struct[i].output_file);
			parsed_struct[i].output_file = NULL;
		}
		if (parsed_struct[i].heredoc)
		{
			free(parsed_struct[i].heredoc);
			parsed_struct[i].heredoc = NULL;
		}
		if (parsed_struct[i].extra)
		{
			free(parsed_struct[i].extra);
			parsed_struct[i].extra = NULL;
		}
		if (parsed_struct[i].fd[0])
		{
			close(parsed_struct[i].fd[0]);
			parsed_struct[i].fd[0] = 0;
		}
		if (parsed_struct[i].fd[1])
		{
			close(parsed_struct[i].fd[1]);
			parsed_struct[i].fd[1] = 0;
		}
		i++;
	}
	free(parsed_struct);
	parsed_struct = NULL;
}
