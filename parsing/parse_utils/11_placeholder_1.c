/* ************************************************************************** */
/*                                                                            */
/*   11_placeholder_1.c             ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_backslashes(const char *str)
{
	char		*new_str;
	char		*p;
	const char	*q;

	new_str = malloc(strlen(str) + 1);
	if (!new_str)
		return (NULL);
	p = new_str;
	q = str;
	while (*q)
	{
		if (*q == '\\' && (*(q + 1) == '\\' || *(q + 1) == '\''
				|| *(q + 1) == '"' || *(q + 1) == '$'
				|| *(q + 1) == '?' || *(q + 1) == '|'))
			q++;
		*p++ = *q++;
	}
	*p = '\0';
	return (new_str);
}

char	**allocate_strings(const char *line, int *num_strings)
{
	char	**strings;

	*num_strings = count_occurrences(line, '"', '\'') / 2;
	strings = (char **)malloc((*num_strings + 1) * sizeof(char *));
	check_malloc(strings);
	return (strings);
}

const char	*find_next_string(const char *start, \
	const char *line, const char **end)
{
	start = ft_strchr(start, *start);
	while (*start && !(*start == '"' || *start == '\'')
		&& (start <= line || *(start - 1) != '\\'))
		start++;
	if (!start)
		return (NULL);
	*end = start + 1;
	while (*(*end) && (*(*end) != *start
			|| (*end > start + 1 && *(*end - 1)
				== '\\' && *(*end - 2) != '\\')))
		*end += 1;
	if (!*end)
		return (NULL);
	return (start);
}

void	process_string_placehoder(char **strings, \
	const char *start, const char *end, int occurrence)
{
	int		length;
	char	*processed_string;

	length = end - start - 1;
	strings[occurrence] = ft_strsub(start + 1, 0, length);
	processed_string = remove_backslashes(strings[occurrence]);
	free(strings[occurrence]);
	strings[occurrence] = processed_string;
}

char	**extract_strings(const char *line, int *numStrings)
{
	char		**strings;
	int			occurrence;
	const char	*start;
	const char	*end;

	strings = allocate_strings(line, numStrings);
	occurrence = 0;
	start = line;
	end = line;
	while (*start && occurrence < *numStrings)
	{
		start = find_next_string(start, line, &end);
		if (!start)
			break ;
		process_string_placehoder(strings, start, end, occurrence);
		occurrence++;
		start = end + 1;
	}
	strings[occurrence] = NULL;
	return (strings);
}
