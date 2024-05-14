/* ************************************************************************** */
/*                                                                            */
/*   2_input_handling.c         ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prepare_line(char *line, char ***ph_strings)
{
	char	*prepared;
	// char	**ph_strings;

	prepared = malloc(strlen(line) + 8192);
	check_malloc(prepared);
	// ph_strings = malloc(strlen(line) + 8192);
	*ph_strings = malloc(sizeof(char **) * (strlen(line) + 8192));
	check_malloc(ph_strings);
	placeholder(line, ph_strings);
printf("Modified line: %s\n", line);
	prepared = ft_strdup(line);
printf("Modified prepared: %s\n", prepared);
printf("Modified ph_strings (prepare_line): \n");
print_ph_strings(ph_strings);
	// handle_input(line, prepared);
	// remove_double_quotes(prepared);
	return (prepared);
}

// handle_quotes(line, &i, &in_quotes); /// CHANGED TO FIX echo "aspas ->'"

void	handle_input(char *line, char *prepared)
	{
	int	i;
	int	j;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (line[i] != '\0')
	{
		if (in_quotes != '\'')
		{
			handle_variables(line, prepared, &i, &j);
		}
		handle_others(line, prepared, &i, &j);
	}
	prepared[j] = '\0';
}

void	handle_others(char *line, char *prepared, int *i, int *j)
{
	if (line[*i] != '\0')
	{
		prepared[*j] = line[*i];
		(*j)++;
		(*i)++;
	}
}

char	*get_last_exit_status(void)
{
	char	*status_str;
	int		status;
	pid_t	pid;

	pid = wait(&status);
	if (pid == -1)
	{
		status_str = ft_strdup("-1");
	}
	else if (WIFEXITED(status))
	{
		status_str = ft_itoa(WEXITSTATUS(status));
	}
	else
	{
		status_str = ft_strdup("Error");
	}
	return (status_str);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}