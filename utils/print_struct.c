/* ************************************************************************** */
/*                                                                            */
/*   print_struct.c             ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_struct(t_main *main, int num_commands)
{
	int		i;
	char	**args;

	i = 0;
	while (i < num_commands)
	{
		printf("%d\n", i);
		printf("Command: %s\n", main[i].cmd);
		printf("Flags: %s\n", main[i].flags);
		args = main[i].args;
		printf("Arguments: \n");
		while (*args != NULL)
		{
			printf("%s \n", *args);
			args++;
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
