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

#include "../minishell.h"

// typedef struct s_main
// {
// 	char	*cmd;
// 	char	*flags;
// 	char	**args;
// 	int		fd[2];
// 	pid_t	pid;
// 	char	*input_file;
// 	char	*output_file;
// }			t_main;

void	print_struct(t_main *main, int num_commands)
{
	int		i;
	// int 	j;
	char	**args;

	i = 0;
	// j = 0;
	while (i < num_commands)
	{
		printf("%d\n", i);
		printf("Command: %s\n", main[i].cmd);
		printf("Flags: %s\n", main[i].flags);
		args = main[i].args;
		printf("Arguments: \n");// DEVERIA CONTAR OS ARGUMENTOS, E IMPRIMIR ATE O ULTIMO?
		while (*args != NULL)
		// while (j < 10)
		{
			printf("%s \n", *args);
			args++;
			// j++;
		}
		printf("Input file: %s\n", main[i].input_file);
		printf("Output file: %s\n", main[i].output_file);
		printf("File descriptor (read end): %d\n", main[i].fd[0]);
		printf("File descriptor (write end): %d\n", main[i].fd[1]);
		printf("PID: %d\n", main[i].pid);
		printf("Heredoc: %s\n", main[i].heredoc);
		printf("\n");
		i++;
	}
}