/* ************************************************************************** */
/*                                                                            */
/*   cleanup_2.c                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_args_2(char ***args)
{
	int	j;

	j = 0;
	if (*args)
	{
		while ((*args)[j])
		{
			free_and_nullify((void **)&(*args)[j]);
			j++;
		}
	}
	free_and_nullify((void **)args);
}
