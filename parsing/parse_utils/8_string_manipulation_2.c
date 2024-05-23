/* ************************************************************************** */
/*                                                                            */
/*   8_string_manipulation_2        ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	dup = NULL;
	len = strlen(s);
	if (n < len)
		len = n;
	dup = (char *)malloc(len + 1);
	if (dup)
	{
		memcpy(dup, s, len);
		dup[len] = '\0';
	}
	return (dup);
}
