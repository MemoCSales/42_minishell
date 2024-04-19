/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:00:03 by demacinema        #+#    #+#             */
/*   Updated: 2024/04/19 15:07:18 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

//CHECKERS
int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_isenv_or_path(char c)
{
	if (c == '$' || c == '/')
		return (1);
	return (0);
}

int ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

//CHECKERS SEPARATORS
int ft_istoken_separator(char c)
{
	// if (ft_strchr(" \t\n\v\f\r", c) != 0)
	// 	return (1);
	if (ft_isspace(c))
		return (1);
	else if (c == ';' || c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int ft_iscmd_separator(char c)
{
	if (c == ';' || c == '|' || c == '&')
		return (1);
	return (0);
}

int ft_iscmdlist_separator(const char *str)
{
	if (*str == ';')
		return (1);
	else if (!ft_strncmp((char *)str, "||", 2))
		return (1);
	else if (!ft_strncmp((char *)str, "&&", 2))
		return (1);
	else
		return (0);
}


//MINI LIBFT
//LISTS
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (!*lst)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

t_list	*ft_lstnew(void *data)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->data = data;
	new_node->next = 0;
	return (new_node);
}

//STRINGS
char	*ft_strncpy(char *dest, char *src, size_t n)
{
	char	*sav_dest;
	char	*sav_src;

	sav_dest = dest;
	sav_src = src;
	if (n != 0)
	{
		while (1)
		{
			*sav_dest = *sav_src++;
			if (*sav_dest++ == 0)
			{
				while (--n != 0)
					*sav_dest++ = 0;
				break ;
			}
			if (--n == 0)
				break ;
		}
	}
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
	{
		new_str = ft_calloc(1, sizeof(char));
		if (!new_str)
			return (0);
		return (new_str);
	}
	new_str = ft_calloc(len + 1, sizeof(char));
	if (!new_str)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	return (0);
}

int ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i]) // if it finds a different character
			return (s1[i] - s2[i]); // return the difference between the first two different characters
		i++;
	}
	
	if (i == n) // if it searched all the characters and they are the same
		return (0);
		
	return (s1[i] - s2[i]); // if one string is shorter than the other, as i != n,
							// returns the difference between the first different character
							// ('\0' and the character in the other string)
}

char	*ft_strdup(const char *s)
{
	int		s_len;
	char	*cpy;

	if (!s)
	{
		cpy = malloc(1);
		if (!cpy)
			return (0);
		*cpy = 0;
		return (cpy);
	}
	s_len = ft_strlen(s) + 1;
	cpy = malloc(s_len * sizeof(char));
	if (!cpy)
		return (0);
	ft_strcpy(cpy, s);
	return (cpy);
}

//MEMORY
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	i = 0;
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}