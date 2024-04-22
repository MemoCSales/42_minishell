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

void	print_struct(t_main *main)
{
	int		i;
	char	**args;

	i = 0;
	while (main[i].cmd != NULL)
	{
		printf("Command: %s\n", main[i].cmd);
		if (main[i].flags != NULL)
			printf("Flags: %s\n", main[i].flags);
		if (main[i].args != NULL)
		{
			args = main[i].args;
			printf("Arguments: ");
			while (*args != NULL)
			{
				printf("%s ", *args);
				args++;
			}
			printf("\n");
		}
		printf("Input file: %s\n", main[i].input_file);
		printf("Output file: %s\n", main[i].output_file);
		printf("File descriptor (read end): %d\n", main[i].fd[0]);
		printf("File descriptor (write end): %d\n", main[i].fd[1]);
		i++;
	}
}