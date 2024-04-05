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

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*cmd[] = {"pwd", NULL}; //This variable is for testing the buildins
	char 	*rl;
	t_env	env_var;

	init_env(&env_var, env); //This function initialize the env_vars
	while (1) //first while loop that prints a prompt and retrieves from what it reads
	{
		rl = readline("\033[0;91mmini\033[1;91mℍ\033[0;91mΞLL>> \033[0m");
		printf("%s\n", rl);
		buildins(&env_var, cmd);
	}
	check_env(&env_var); //In this function it checks env_vars and frees the memory. 
	return(0);
}
