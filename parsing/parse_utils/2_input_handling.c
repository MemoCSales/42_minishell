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
int g_status;

char *change_unquoted_dollar_signs(char *str)
{
    char *result = malloc(strlen(str) * 2); // Allocate memory for the result string
    int i = 0, j = 0;
    int in_double_quotes = 0;
    int in_single_quotes = 0;
    while (str[i] != '\0') {
        if (str[i] == '"') {
            in_double_quotes = !in_double_quotes; // Toggle the in_double_quotes flag
        }
        if (str[i] == '\'') {
            in_single_quotes = !in_single_quotes; // Toggle the in_single_quotes flag
        }
        if (!in_double_quotes && !in_single_quotes && str[i] == '$') {
            int start = i;
            while (str[i] != ' ' && str[i] != '\0') {
                i++;
            }
            int len = i - start;
            strncpy(&result[j], "\"", 1);
            strncpy(&result[j + 1], &str[start], len);
            strncpy(&result[j + len + 1], "\"", 1);
            j += len + 2;
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0'; // Null-terminate the result string
    return result;
}


void	clean_string(char *str)
{
	int	i;
	int	j;
	int	length;

	i = 0;
	j = 0;
	length = strlen(str);
	while (i < length)
	{
		if (str[i] == '\\'
			&& (str[i + 1] == '"' || str[i + 1] == '$'))
		{
			i++;
		}
		str[j] = str[i];
		j++;
		i++;
	}
	str[j] = '\0';
}

char	*handle_variables(char *line)
{
	char	*result;
	char	*env_var_start;
	char	*env_var_end;
	char	*status;
	int		i;
	int		j;
	int		quotes;

	i = 0;
	j = 0;
	env_var_start = NULL;
	env_var_end = NULL;
	status = NULL;
	result = malloc(strlen(line) * 200);

	line = change_unquoted_dollar_signs(line); //PUTS DOUBLE QUOTES TO CHANGE IF NO QUOTES
// printf("MODIFIED LINE: %s\n", line);

	quotes = 0;

	if (ft_strchr(line, '$'))//TEM DOLAR?
	{
// printf ("$\n");
		quotes = is_char_in_quotes(line, ft_strchr(line, '$') - line);
		if (quotes == 0)//FORA DE ASPAS?
		{
// printf ("$ OUTSIDE QUOTES\n");
			env_var_start = &line[ft_strchr(line, '$') - line];
			env_var_end = env_var_start;
			env_var_end++;
// printf("env_var_start:%c, env_var_end:%c\n", *env_var_start, *env_var_end);
			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
				env_var_end++;
// printf("env_var_start:%c, env_var_end:%c\n", *(env_var_start), *(env_var_end - 1));
			char env_var_name[env_var_end - (env_var_start + 1)];
			ft_strncpy(env_var_name, env_var_start + 1, ((env_var_end) - (env_var_start)));
			env_var_name[env_var_end - env_var_start] = '\0';
// printf("env_var_name: %s\n", env_var_name);
			char *env_var_value = getenv(env_var_name);
// printf("env_var_value: %s\n", env_var_value);
			if (env_var_value != NULL)
			{
				strcpy(&result[j], env_var_value);
				j += strlen(env_var_value);
			}
			i = env_var_end - line;
		}
	}
// printf("RESULT FORA QUOTES:%s\n", result);

	i = 0;
	quotes = ft_strchr(line, '$') - line;
	if (quotes >= 0)
		quotes = is_char_in_quotes(line, quotes);

	while (line[i] != '\0')
	{
		if ((line[i] == '$' && (i == 0 || line[i - 1] != '\\'))
			&& (quotes == 2) && (line[i + 1] != ' ') && (line [i + 1] != '?')
			&& (line[i + 1] != '\'' && line[i + 1] != '\"'))
		{
// printf("\"$\"");
			env_var_start = &line[i + 1];
			env_var_end = env_var_start;
			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
				env_var_end++;
			char env_var_name[env_var_end - env_var_start + 1];
			ft_strncpy(env_var_name, env_var_start, (env_var_end - env_var_start));
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
		else if (line[i] == '$' && line[i + 1] == '?' && quotes != 1 && line[i - 1] != '\\')//&& (quotes == 2)
		{
			status = ft_itoa(g_status);
// printf("status: %s\n", status);
			ft_strcpy(&result[j], status);
			j += ft_strlen(status);
			i += 2;
// printf("RESULT:%s\n", result);
		}
		else
		{
			if (line[i] == '\\' && line[i + 1] == '$')
			{
				result[j++] = '$';
				i += 2;
			}
			else
			{
				result[j++] = line[i++];
			}
		}
	}
// printf("RESULT:%s\n", result);
	result[j] = '\0';
// printf("result:%s\n", result);
	return (result);
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
// printf("prepared_handlevairables: %s\n", prepared);
	// clean_string(prepared);
	// remove_double_quotes(prepared);
// printf("prepared_cleanstrings: %s\n", prepared);
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


// char *modify_string(char *line) 
// {
//     char *modified_line;
//     char *found_char;

//     modified_line = line;

//     // Check for backslash and call handle_backslash if found
//     found_char = strchr(modified_line, '\\');
//     if (found_char != NULL) 
//     {
//         modified_line = handle_backslash(modified_line);
//     }

//     // Check for dollar sign and call handle_dollar_sign if found
//     found_char = strchr(modified_line, '$');
//     if (found_char != NULL) 
//     {
//         modified_line = handle_dollar_sign(modified_line);
//     }

//     return (modified_line);
// }

// char	*handle_variables(char *line)
// {
// 	char	*result;
// 	char	*env_var_start;
// 	char	*env_var_end;
// 	// char	*env_var_name;
// 	// char	*env_var_value;
// 	char	*status;
// 	int		i;
// 	int		j;
// 	int		quotes;

// 	i = 0;
// 	j = 0;
// 	env_var_start = NULL;
// 	env_var_end = NULL;
// 	status = NULL;
// 	result = malloc(strlen(line) * 200);
// 	quotes = 0;
// 	if (ft_strchr(line, '$'))
// 	{
// 		quotes = is_char_in_quotes(line, ft_strchr(line, '$') - line);
// 		if (quotes == 0)
// 		{
// 			env_var_start = &line[ft_strchr(line, '$') - line];
// 			env_var_end = env_var_start;
// 			env_var_end++;
// 			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
// 				env_var_end++;
// 			env_var_name[env_var_end - (env_var_start + 1)];
// 			ft_strncpy(env_var_name, env_var_start + 1,
// 				((env_var_end) - (env_var_start)));
// 			env_var_name[env_var_end - env_var_start] = '\0';
// 			env_var_value = getenv(env_var_name);
// 			if (env_var_value != NULL)
// 			{
// 				strcpy(&result[j], env_var_value);
// 				j += strlen(env_var_value);
// 			}
// 			i = env_var_end - line;
// 		}
// 	}
// 	i = 0;
// 	quotes = ft_strchr(line, '$') - line;
// 	if (quotes >= 0)
// 		quotes = is_char_in_quotes(line, quotes);
// 	while (line[i] != '\0')
// 	{
// 		if ((line[i] == '$' && (i == 0 || line[i - 1] != '\\'))
// 			&& (quotes == 2) && (line[i + 1] != ' ') && (line [i + 1] != '?')
// 			&& (line[i + 1] != '\'' && line[i + 1] != '\"'))
// 		{
// 			env_var_start = &line[i + 1];
// 			env_var_end = env_var_start;
// 			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
// 				env_var_end++;
// 			char env_var_name[env_var_end - env_var_start + 1];
// 			ft_strncpy(env_var_name, env_var_start,(env_var_end - env_var_start));
// 			env_var_name[env_var_end - env_var_start] = '\0';
// 			char *env_var_value = getenv(env_var_name);
// 			if (env_var_value != NULL)
// 			{
// 				strcpy(&result[j], env_var_value);
// 				j += strlen(env_var_value);
// 			}
// 			i = env_var_end - line;
// 		}//&& (quotes == 2)
// 		else if (line[i] == '$' && line[i + 1] == '?'
// 			&& quotes != 1 && line[i - 1] != '\\')
// 		{
// 			status = ft_itoa(g_status);
// 			ft_strcpy(&result[j], status);
// 			j += ft_strlen(status);
// 			i += 2;
// 		}
// 		else
// 		{
// 			if (line[i] == '\\' && line[i + 1] == '$')
// 			{
// 				result[j++] = '$';
// 				i += 2;
// 			}
// 			else
// 			{
// 				result[j++] = line[i++];
// 			}
// 		}
// 	}
// 	result[j] = '\0';
// 	return (result);
// }