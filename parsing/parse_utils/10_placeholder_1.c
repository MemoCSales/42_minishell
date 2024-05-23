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
//MOVED TO 12_PLACEHOLDER_3
// char	*generate_placeholder(int occurrence, char quote_type)
// {
// 	char	*occurrence_str;
// 	char	*placeholder;
// 	char	*symbol;

// 	if (quote_type == '\'')
// 	{
// 		symbol = "ψ";
// 	}
// 	else
// 	{
// 		symbol = "Ψ";
// 	}
// 	occurrence_str = ft_itoa(occurrence + 1);
// 	placeholder = malloc(strlen(symbol) + strlen("()") 
// 	+ strlen(occurrence_str) + 1);
// 	strcpy(placeholder, symbol);
// 	strcat(placeholder, "(");
// 	strcat(placeholder, occurrence_str);
// 	strcat(placeholder, ")");
// 	free(occurrence_str);
// 	return (placeholder);
// }

// void	replace_with_placeholder(char *line)
// {
// 	int		occurrence;
// 	char	*st;
// 	char	*end;
// 	char	*ph;

// 	occurrence = 0;
// 	st = line;
// 	end = line;
// 	while (*st)
// 	{
// 		while (*st && !(*st == '"' || *st == '\'')
// 			&& (st <= line || *(st - 1) != '\\'))
// 			st++;
// 		if (!*st)
// 			break ;
// 		end = st + 1;
// 		while (*end && (*end != *st || (end > st + 1 && *(end - 1)
// 					== '\\' && *(end - 2) != '\\')))
// 			end++;
// 		ph = generate_placeholder(occurrence++, *st);
// 		memmove(st + ft_strlen(ph), end + 1, ft_strlen(end + 1) + 1);
// 		memcpy(st, ph, strlen(ph));
// 		st += ft_strlen(ph);
// 		free(ph);
// 	}
// }

// int	count_occurrences(const char *str, char c, char d)
// {
// 	int	count;

// 	count = 0;
// 	while (*str)
// 	{
// 		if (*str == c || *str == d)
// 			count++;
// 		str++;
// 	}
// 	return (count);
// }

// char	*ft_strsub(char const *s, unsigned int start, size_t len)
// {
// 	char		*substring;
// 	size_t		i;

// 	if (!s)
// 		return (NULL);
// 	substring = (char *)malloc((len + 1) * sizeof(char));
// 	if (!substring)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i] != '\0')
// 	{
// 		substring[i] = s[start + i];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }

// // ANTES DE MUDAR
// void	replace_with_placeholder(char *line)
// {
// 	int		occurrence;
// 	char	*st;
// 	char	*end;
// 	char	*ph;

// 	occurrence = 0;
// 	st = line;
// 	end = line;
// 	while (*st)
// 	{
// 		while (*st && !(*st == '"' || *st == '\'')
// 			&& (st <= line || *(st - 1) != '\\'))
// 			st++;
// 		if (!*st)
// 			break ;
// 		end = st + 1;
// 		while (*end && (*end != *st || (end > st + 1 && *(end - 1)
// 					== '\\' && *(end - 2) != '\\')))
// 			end++;
// 		ph = generate_placeholder(occurrence, *st);
// 		memmove(st + ft_strlen(ph), end + 1, ft_strlen(end + 1) + 1);
// 		memcpy(st, ph, strlen(ph));
// 		st += ft_strlen(ph);
// 		occurrence++;
// 		free(ph);
// 	}
// }

// ANTES DE QUEBRAR
// char	**extract_strings(const char *line, int *numStrings)
// {
// 	char		**strings;
// 	int			occurrence;
// 	int			length;
// 	const char	*start;
// 	const char	*end;
// 	char		*processed_string;

// 	*numStrings = count_occurrences(line, '"', '\'') / 2;
// 	strings = (char **)malloc((*numStrings + 1) * sizeof(char *));
// 	check_malloc(strings);
// 	occurrence = 0;
// 	start = line;
// 	end = line;
// 	while (*start && occurrence < *numStrings)
// 	{
// 		start = ft_strchr(start, *start);
// 		while (*start && !(*start == '"' || *start == '\'')
// 			&& (start <= line || *(start - 1) != '\\'))
// 			start++;
// 		if (!start)
// 			break ;
// 		end = start + 1;
// 		while (*end && (*end != *start || (end > start + 1
// 					&& *(end - 1) == '\\' && *(end - 2) != '\\')))
// 			end++;
// 		if (!end)
// 			break ;
// 		length = end - start - 1;
// 		strings[occurrence] = ft_strsub(start + 1, 0, length);
// 		processed_string = remove_backslashes(strings[occurrence]);
// 		free(strings[occurrence]);
// 		strings[occurrence] = processed_string;
// 		occurrence++;
// 		start = end + 1;
// 	}
// 	strings[occurrence] = NULL;
// 	return (strings);
// }

//ANTIGA
// char	*generate_placeholder(int occurrence)
// {
// 	char	*occurrence_str;
// 	char	*placeholder;

// 	occurrence_str = ft_itoa(occurrence + 1);
// 	placeholder = malloc(strlen("Ψ()") + strlen(occurrence_str) + 1);
// 	strcpy(placeholder, "Ψ(");
// 	strcat(placeholder, occurrence_str);
// 	strcat(placeholder, ")");
// 	free(occurrence_str);
// 	return (placeholder);
// }

//ANTIGA
// void replace_with_placeholder(char *line)
// {
// 	int occurrence;
// 	char *st;
// 	char *end;
// 	char *ph;

// 	occurrence = 0;
// 	st = line;
// 	end = line;
// 	while (*st)
// 	{
// 		while (*st && !(*st == '"' || *st == '\'')
		// && (st <= line || *(st - 1) != '\\'))
// 			st++;
// 		if (!*st)
// 			break;
// 		end = st + 1;
// 		while (*end && *end != *st)
// 			end++;
// 		ph = generate_placeholder(occurrence, *st);
// 		memmove(st + ft_strlen(ph), end + 1, ft_strlen(end + 1) + 1);
// 		memcpy(st, ph, strlen(ph));
// 		st += ft_strlen(ph);
// 		occurrence++;
// 		free(ph);
// 	}
// }
// // Function to replace strings between double quotes with placeholders
// void	replace_with_placeholder(char *line)
// {
// 	int		occurrence;
// 	char	*st;
// 	char	*end;
// 	char	*ph;

// 	occurrence = 0;
// 	st = line;
// 	end = line;
// 	while (*st)
// 	{
// 		while (*st && !(*st == '"' || *st == '\'')
// 			&& (st <= line || *(st - 1) != '\\'))
// 			st++;
// 		if (!*st)
// 			break ;
// 		end = st + 1;
// 		while (*end && *end != *st)
// 			end++;
// 		ph = generate_placeholder(occurrence);
// 		memmove(st + ft_strlen(ph), end + 1, ft_strlen(end + 1) + 1);
// 		memcpy(st, ph, strlen(ph));
// 		st += ft_strlen(ph);
// 		occurrence++;
// 		free(ph);
// 	}
// }

//ANTIGA
// char **extract_strings(const char *line, int *numStrings)
// {
// 	char **strings;
// 	int occurrence;
// 	int length;
// 	const char *start;
// 	const char *end;
// 	const char *start_double;
// 	const char *start_single;

// 	*numStrings = count_occurrences(line, '"', '\'') / 2;
// 	strings = (char **)malloc((*numStrings + 1) * sizeof(char *));
// 	check_malloc(strings);
// 	occurrence = 0;
// 	start = line;
// 	end = line;
// 	while (*start && occurrence < *numStrings)
// 	{
// 		start_double = ft_strchr(start, '"');
// 		start_single = ft_strchr(start, '\'');
// 		if (!start_double && !start_single)
// 			break;
// 		if (!start_single || (start_double && start_double < start_single))
// 			start = start_double;
// 		else
// 			start = start_single;
// 		end = ft_strchr(start + 1, *start);
// 		if (!end)
// 			break;
// 		length = end - start - 1;
// 		strings[occurrence] = ft_strsub(start + 1, 0, length);
// 		occurrence++;
// 		start = end + 1;
// 	}
// 	strings[occurrence] = NULL;
// 	return (strings);
// }

//ANTIGA
// int	count_occurrences(const char *str, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*str)
// 	{
// 		if (*str == c)
// 			count++;
// 		str++;
// 	}
// 	if (count % 2 != 0)
// 	{
// 		printf("Warning: Unclosed double quotes.\n");
// 	}
// 	return (count);
// }