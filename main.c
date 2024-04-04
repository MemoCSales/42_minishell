/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*cmd[] = {"pwd", NULL};
	char *rl;

	// init_env();
	while (1)
	{
    	rl = readline("\033[0;91m₼ℹnℹ\033[1;91mℍ\033[0;91mΞLL> \033[0m");
    	printf("%s\n", rl);
	}
	buildins(cmd);
	printf("Hello minishell\n");
	return(0);
}