/* ************************************************************************** */
/*                                                                            */
/*   echo.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_code(t_env *env)
{
	printf("%d\n", env->status);
}

char	*ft_strremove(char *string, int c)
{
	char	*new;
	char	*new_start;

	new = malloc(ft_strlen(string) + 1);
	if (!new)
	{
		ft_putstr_fd("Error allocating memory: echo", 2);
		exit(0);
	}
	new_start = new;
	while (*string)
	{		
		if (*string != c)
			*new++ = *string;
		string++;
	}
	*new = '\0';
	return (new_start);
}

int	echo_builtin(t_main *main, t_env *env)
{
	int		i;
	int		cut_newline;
	char	*arg;
	char	*arg_no_quotes;

	cut_newline = 0;
	if (ft_strcmp(main->args[0], "$?") == 0)
	{
		exit_code(env);
		return (0);
	}
	if (ft_strcmp(main->flags, "-n") == 0 && main->flags != NULL)
		cut_newline = 1;
	i = 0;
	while (main->args[i] != NULL)
	{
		arg = main->args[i];
		arg_no_quotes = ft_strremove(arg, '\'');
		if (printf("%s", arg_no_quotes) < 0)
		{
			free(arg_no_quotes);
			return (1);
		}
		if (main->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!cut_newline)
		printf("\n");
	return (0); // Set status to 0 if success
}

