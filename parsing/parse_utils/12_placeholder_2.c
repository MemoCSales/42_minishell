/* ************************************************************************** */
/*                                                                            */
/*   12_placeholder_2.c             ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
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

void	replace_placeholder_sub(char **str, \
		char *placeholder, char *replacement)
{
	char	*pos;
	char	*new_str;

	if (*str != NULL && placeholder != NULL)
	{
		pos = strstr(*str, placeholder);
		if (pos != NULL)
		{
			new_str = malloc(strlen(*str) - strlen(placeholder) \
			+ strlen(replacement) + 1);
			check_malloc(new_str);
			ft_memcpy(new_str, *str, pos - *str);
			new_str[pos - *str] = '\0';
			ft_strcpy(new_str + (pos - *str), replacement);
			ft_strcpy(new_str + (pos - *str) + ft_strlen(replacement), \
			pos + ft_strlen(placeholder));
			free(*str);
			*str = new_str;
		}
	}
}

// CHANGE WHILE IN CASE ISSUES: while (*i < 10)
void	handle_psi(char **str, char ***ph_strings, int *i)
{
	char	*placeholder;
	char	*replacement;
	char	*temp;

	while ((*ph_strings)[*i] != NULL)
	{
		temp = ft_itoa((*i) + 1);
		placeholder = ft_strjoin("Ψ(", temp);
		free(temp);
		if (!placeholder)
			return ;
		temp = placeholder;
		placeholder = ft_strjoin(placeholder, ")");
		free(temp);
		if (!placeholder)
			return ;
		replacement = (*ph_strings)[*i];
		if (!replacement)
			return ;
		replace_placeholder_sub(str, placeholder, replacement);
		free(placeholder);
		(*i)++;
	}
}

void	handle_psi_lower(char **str, char ***ph_strings, int *i)
{
	char	*placeholder;
	char	*replacement;
	char	*temp;

	while ((*ph_strings)[*i] != NULL)
	{
		temp = ft_itoa((*i) + 1);
		placeholder = ft_strjoin("ψ(", temp);
		free(temp);
		if (!placeholder)
			return ;
		temp = placeholder;
		placeholder = ft_strjoin(placeholder, ")");
		free(temp);
		if (!placeholder)
			return ;
		replacement = (*ph_strings)[*i];
		if (!replacement)
			return ;
		replace_placeholder_sub(str, placeholder, replacement);
		free(placeholder);
		(*i)++;
	}
}

void	reverse_placeholders(char **str, char ***ph_strings)
{
	int		i;
	int		j;
	size_t	len;

	if (!str || !*str || !ph_strings || !*ph_strings)
		return ;
	i = 0;
	len = ft_strlen(*str);
	if (ft_strnstr(*str, "Ψ", len) != NULL)
	{
		handle_psi(str, ph_strings, &i);
		j = 0;
		while (*str != NULL && (*str)[j] != '\0')
		{
			handle_variables_ph(*str, str, &j, &j);
			j++;
		}
	}
	else if (ft_strnstr(*str, "ψ", len) != NULL)
	{
		handle_psi_lower(str, ph_strings, &i);
	}
}
