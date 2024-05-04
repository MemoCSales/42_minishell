/* ************************************************************************** */
/*                                                                            */
/*   main.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
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
	// main_var = initialize_main(main_var); // initialize main_vars
	init_env(&env_var, env); // initialize env_vars
	main_loop(env_var, main_var);
	check_env(&env_var); // checks env_vars, frees the memory. needed?
	return (0);
}
