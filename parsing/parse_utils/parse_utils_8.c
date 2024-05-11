/* ************************************************************************** */
/*                                                                            */
/*   parse_utils_8.c            ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	if (!dst || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	src_len;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == NULL)
		return (dest);
	if (src == NULL)
		return (dest);
	src_len = ft_strlen(src);
	if (n > src_len)
	{
		ft_memcpy(dest, src, src_len);
		dest[src_len] = '\0';
	}
	else
	{
		ft_memcpy(dest, src, n);
		dest[n] = '\0';
	}
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	src_len;
	char	*temp;

	dest_len = strlen(dest);
	src_len = strlen(src);
	temp = NULL;
	temp = malloc(dest_len + src_len + 1);
	check_malloc(temp);
	ft_strncpy(temp, dest, dest_len);
	ft_strncpy(temp + dest_len, (char *)src, src_len);
	temp[dest_len + src_len] = '\0';
	ft_strcpy(dest, temp);
	free(temp);
	return (dest);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_escaped(char *line, int index)
	{
	int	count;

	count = 0;
	index--;
	while (index >= 0 && line[index] == '\\')
	{
		count++;
		index--;
	}
	return (count % 2 != 0);
}
