/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 20:59:51 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_main	*redirection(t_main *parsed_struct, char **args, int i, int j)
{
	char	*delimiter;
	char	*heredoc;
	// int		x = 1; // DEBUG
	int		x = 0; // DEBUG

	heredoc = NULL;
	
// ">>" APPEND
	if (ft_strcmp(args[j], ">>") == 0
		&& args[j + 1])
	{
		if (x)
			printf("ENTROU NO >> APPEND\n");
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
		parsed_struct[i].extra = ft_strdup(args[j]);
		//passing ">>" to *extra, to signal that it is a append
		remove_args(args, j, 2);
		return (&parsed_struct[i]);
		// break ;
	}
	// "<<" HEREDOC
	else if (ft_strcmp(args[j], "<<") == 0
		&& args[j + 1]) // Check for heredoc
	{
		if (x){
			printf ("ENTROU NO << HEREDOC\n");
			printf("HEREDOC [J]: %d\n\n", j);}
				
		delimiter = args[j + 1];
		heredoc = read_heredoc(delimiter);
		parsed_struct[i].heredoc = heredoc;
		remove_args (args, j, 2);
		return (&parsed_struct[i]);
		// break ;
	}
	// "<" INPUT
	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
	{
		if (x)
			printf("\n\"<\" INPUT \n\n");
			
		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
		remove_args(args, j, 2);
		return (&parsed_struct[i]);
		// break ;
	}
	// ">" OUTPUT
	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
	{
		if (x)
			printf("\n\">\" OUTPUT\n\n");
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
		remove_args(args, j, 2);
		return (&parsed_struct[i]);
		// break ;
	}
	return (&parsed_struct[i]);
	// NO WEIRD STUFF
// 	else
// 	{
// 		// printf("\n\nARG NO WEIRD STUFF: %s\n", args[j]);
// 		// printf("NO WEIRD STUFF\n");
// 		j++;
// 	}
}

void	print_args(char **args)
{
	int k;

	k = 0;
	printf("\n");
	// printf("ARGS[%d]: %s\n", k, args[k]);
	if (!args)
		printf("Argument %d: %s\n", k, args[k]);
	else
	{
		while (args[k] != NULL)
		{
			printf("Argument %d: %s\n", k, args[k]);
			k++;
		}
	}
	printf("\n");
}

void	print_struct(t_main *main_var, int i)
{
	printf("\nt_main[%d].cmd: %s\n", i, main_var[i].cmd);
	printf("t_main[%d].flags: %s\n", i, main_var[i].flags);
	printf("t_main[%d].input_file: %s\n", i, main_var[i].input_file);
	printf("t_main[%d].output_file: %s\n", i, main_var[i].output_file);
	printf("t_main[%d].heredoc: %s\n", i, main_var[i].heredoc);
	printf("t_main[%d].extra: %s\n", i, main_var[i].extra);
	printf("t_main[%d].fd[0]: %d\n", i, main_var[i].fd[0]);
	printf("t_main[%d].fd[1]: %d\n\n", i, main_var[i].fd[1]);
}

void	check_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

int	check_redir(char **args, int j)// COM ESPACOS OU SEM ESPACOS?
{
	if (ft_strcmp(args[j], ">>") == 0
		|| ft_strcmp(args[j], "<<") == 0
		|| ft_strcmp(args[j], "<") == 0
		|| ft_strcmp(args[j], ">") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// char	*prepared_input(char *line)
// {
// 	char	*prepared;
// 	int		i;
// 	int		j;

// 	prepared = malloc(ft_strlen(line) + 1);
// 	if (!prepared)
// 	{
// 		ft_putstr_fd("Error: Unable to allocate memory\n", STDERR_FILENO);
// 		return (NULL);
// 	}
// 	i = 0;
// 	j = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '>' || line[i] == '<')
// 		{
// 			prepared[j++] = ' ';
// 			prepared[j++] = line[i++];
// 			prepared[j++] = ' ';
// 		}
// 		else
// 			prepared[j++] = line[i++];
// 	}
// 	prepared[j] = '\0';
// 	return (prepared);
// }

// void	print_flags(char **flags)
// {
// 	int k;
	
// 	k= 0;
// 	printf("\n");
// 	while (flags[k] != NULL)
// 	{
// 		printf("Flag %d: %s\n", k, flags[k]);
// 		k++;
// 	}
// 	printf("\n");
// }