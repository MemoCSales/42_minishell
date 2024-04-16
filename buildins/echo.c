/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:37:46 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/04/02 13:37:47 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_buildin(t_main *main)
{
	int	i;
	int	cut_newline;

	cut_newline = 0;
	if (ft_strcmp(main->flags, "-n") == 0 && main->flags != NULL)
	{
		cut_newline = 1;
	}
	i = 0;
	while (main->args[i] != NULL)
	{
		printf("%s", main->args[i]);
		if (main->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!cut_newline)
		printf("\n");
}
