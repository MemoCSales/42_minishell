/* ************************************************************************** */
/*                                                                            */
/*   7_string_manipulation.c    ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
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

char	*ft_strswap(char *str, char *substr, char *replacement)
{
	char	*new_str;
	char	*temp;
	size_t	substr_len;

	temp = NULL;
	if (!str || !substr || !replacement)
		return (NULL);
	substr_len = ft_strlen(substr);
	new_str = ft_strdup("");
	while (*str != '\0')
	{
		temp = new_str;
		if (ft_strncmp(str, substr, substr_len) == 0)
		{
			new_str = ft_strjoin(new_str, replacement);
			str += substr_len;
		}
		else
		{
			new_str = ft_strnjoin(new_str, str, 1);
			str++;
		}
		free(temp);
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
