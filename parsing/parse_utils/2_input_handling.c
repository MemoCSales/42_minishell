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

char	*handle_variables(char *line)
{
	char	*result;
	char	*env_var_start;
	char	*env_var_end;
	int		i;
	int		j;
	int		quotes;

	i = 0;
	j = 0;
	env_var_start = NULL;
	env_var_end = NULL;


	quotes = 0;
	quotes = ft_strchr(line, '$') - line;
// printf("\nZ.index: %d\n", quotes);
	if (quotes >= 0)
		quotes = is_char_in_quotes(line, quotes);
	else
		quotes = 0;
// printf("\nY.index: %d\n", quotes);

	result = malloc(strlen(line) * 200);
	while (line[i] != '\0')
	{ //SO TROCA A ENV VAR SE:
		if ((line[i] == '$' && (i == 0 || line[i - 1] != '\\'))
			&& (quotes == 2) && (line[i + 1] != ' ')
			&& (line[i + 1] != '\'' && line[i + 1] != '\"'))
		{
// printf("B.line[i]: %c, line[i - 1]: %c, line[i + 1]: %c\n", line[i], line[i - 1], line[i + 1]);
            env_var_start = &line[i + 1];
			env_var_end = env_var_start;

			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
				env_var_end++;
			
			// env_var_end = ft_strchr(env_var_start, ' ');

            // if (env_var_end == NULL)
			// {
            //     env_var_end = strchr(env_var_start, '\0');
            // }
			// if (env_var_end < env_var_start)
			// {
			// 	// Handle error, e.g. by skipping this variable
			// 	i++;
			// 	continue;
			// }



            char env_var_name[env_var_end - env_var_start + 1];
            ft_strncpy(env_var_name, env_var_start, env_var_end - env_var_start);
            env_var_name[env_var_end - env_var_start] = '\0';
// printf("env_var_name: %s\n", env_var_name);
// printf("env_var_value: %s\n", getenv(env_var_name));
            char *env_var_value = getenv(env_var_name);
// printf("env_var_value2: %s\n", env_var_value);
            if (env_var_value != NULL)
			{
                strcpy(&result[j], env_var_value);
                j += strlen(env_var_value);
            }

            i = env_var_end - line;
// printf("i: %d\n", i);
        }
		else
		{
            result[j++] = line[i++];
        }
    }

    result[j] = '\0';
// printf("result: %s\n", result);
    return result;
}

char	*prepare_line(char *line, char ***ph_strings)
{
	char	*prepared;

	prepared = malloc(strlen(line) + 8192);
	check_malloc(prepared);
	prepared = check_closed_quotes(line);
	if ((ft_strequ(prepared, "\'") || ft_strequ(prepared, "\"")))
	{
		printf("Error: Unclosed quotes (%c)\n", prepared[0]);
		free(prepared);
		prepared = ft_strdup("\0");
		// prepared = ft_strdup("A");
// printf("PPPPPPprepared:%s\n", prepared);
		check_malloc(prepared);
		return (prepared);
	}

	prepared = handle_variables(line);
// printf("prepared222: %s\n", prepared);

	*ph_strings = malloc(sizeof(char **) * (strlen(line) + 8192));
	check_malloc(ph_strings);
	// placeholder(line, ph_strings);
	placeholder(prepared, ph_strings);
// printf("5.PREPARED: %s LINE: %s\n", prepared, line);
	// prepared = ft_strdup(line);
	return (prepared);
	// return (line);
}

// void	handle_input(char *line, char *prepared)
// 	{
// 	int	i;
// 	int	j;
// 	int	in_quotes;

// 	i = 0;
// 	j = 0;
// 	in_quotes = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (in_quotes != '\'')
// 		{
// 			handle_variables(line, prepared, &i, &j);
// 		}
// 		handle_others(line, prepared, &i, &j);
// 	}
// 	prepared[j] = '\0';
// }

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

// char	*prepare_line(char *line, char ***ph_strings)
// {
// 	char	*prepared;
// 	// char	**ph_strings;

// 	prepared = malloc(strlen(line) + 8192);
// 	check_malloc(prepared);
// 	// ph_strings = malloc(strlen(line) + 8192);
// 	*ph_strings = malloc(sizeof(char **) * (strlen(line) + 8192));
// 	check_malloc(ph_strings);
// 	placeholder(line, ph_strings);
// printf("Modified line: %s\n", line);
// 	prepared = ft_strdup(line);
// printf("Modified prepared: %s\n", prepared);
// printf("Modified ph_strings (prepare_line): \n");
// print_ph_strings(ph_strings);
// 	// handle_input(line, prepared);
// 	// remove_double_quotes(prepared);
// 	return (prepared);
// }

// handle_quotes(line, &i, &in_quotes); /// CHANGED TO FIX echo "aspas ->'"