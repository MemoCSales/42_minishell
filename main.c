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

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_main	*main_var;
	t_env	env_var;

	(void)argc;
	(void)argv;
	main_var = NULL;
	init_env(&env_var, env);
	main_loop(env_var, main_var);
	return (0);
}

// EXCLUIDO DA LINHA 25
// //check_env(&env_var);