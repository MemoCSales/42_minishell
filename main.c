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

int	main(int argc, char **argv, char **env)
{
	t_main	*main_var;
	t_env	env_var;

	(void)argc;
	(void)argv;
	main_var = NULL;
	// main_var = initialize_main(main_var); // This function initialize the main_vars
	init_env(&env_var, env);	// This function initialize the env_vars
	main_loop(env_var, main_var);
	check_env(&env_var);	// In this function it checks env_vars and frees the memory. Need to check if its needed
	return (0);
}
