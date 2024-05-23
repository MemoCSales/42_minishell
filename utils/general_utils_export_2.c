/* ************************************************************************** */
/*                                                                            */
/*   general_utils_export.c     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_first_char(char *var)
{
	if (!var || !ft_isalpha(var[0]) || ft_strchr(var, '=')
		|| ft_isdigit(var[0]))
	{
		print_invalid_identifier(var);
		return (0);
	}
	return (1);
}

int	is_valid_remaining_chars(char *var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && (var[i] != '_' || var[i] != '-'))
		{
			print_invalid_identifier(var);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

int	is_all_uppercase(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_isupper(var[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_var_name(char *var)
{
	if (!is_valid_first_char(var))
		return (0);
	if (!is_valid_remaining_chars(var))
		return (0);
	if (!is_all_uppercase(var))
		return (0);
	return (1);
}
