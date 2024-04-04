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
	char *rl;

	//first while loop that prints a prompt and retrieves from what it reads
	while (1)
	{
		rl = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
		printf("%s\n", rl);
	}
	printf("Hello minishell\n");
	return(0);
}