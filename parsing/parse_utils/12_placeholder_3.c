/* ************************************************************************** */
/*                                                                            */
/*   12_placeholder_3.c             ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_placeholder(int occurrence, char quote_type)
{
	char	*occurrence_str;
	char	*placeholder;
	char	*symbol;

	if (quote_type == '\'')
	{
		symbol = "ψ";
	}
	else
	{
		symbol = "Ψ";
	}
	occurrence_str = ft_itoa(occurrence + 1);
	placeholder = malloc(strlen(symbol) + strlen("()") \
	+ strlen(occurrence_str) + 1);
	strcpy(placeholder, symbol);
	strcat(placeholder, "(");
	strcat(placeholder, occurrence_str);
	strcat(placeholder, ")");
	free(occurrence_str);
	return (placeholder);
}

void	replace_with_placeholder(char *line)
{
	int		occurrence;
	char	*st;
	char	*end;
	char	*ph;

	occurrence = 0;
	st = line;
	end = line;
	while (*st)
	{
		while (*st && !(*st == '"' || *st == '\'')
			&& (st <= line || *(st - 1) != '\\'))
			st++;
		if (!*st)
			break ;
		end = st + 1;
		while (*end && (*end != *st || (end > st + 1 && *(end - 1)
					== '\\' && *(end - 2) != '\\')))
			end++;
		ph = generate_placeholder(occurrence++, *st);
		memmove(st + ft_strlen(ph), end + 1, ft_strlen(end + 1) + 1);
		memcpy(st, ph, strlen(ph));
		st += ft_strlen(ph);
		free(ph);
	}
}

int	count_occurrences(const char *str, char c, char d)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c || *str == d)
			count++;
		str++;
	}
	return (count);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t		i;

	if (!s)
		return (NULL);
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
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
