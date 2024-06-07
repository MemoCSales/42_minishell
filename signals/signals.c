/* ************************************************************************** */
/*                                                                            */
/*   signals.c                  ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	siginit_handler(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig_num)
{
	(void)sig_num;
}

void	setup_signals(void)
{
	signal(SIGINT, siginit_handler);
	signal(SIGQUIT, SIG_IGN);
}
