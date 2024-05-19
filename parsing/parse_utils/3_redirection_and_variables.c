/* ************************************************************************** */
/*                                                                            */
/*   3_redirection_and_variables.c     ψΨ MiniℍΞLL Ψψ     :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redir(char **args, int j)
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

void	redirection(t_main *parsed_struct, char **args, int i, int j)
{
	char	*delimiter;
	char	*heredoc;

	heredoc = NULL;
	if (ft_strcmp(args[j], ">>") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
		parsed_struct[i].extra = ft_strdup(args[j]);
	}
	else if (ft_strcmp(args[j], "<<") == 0 && args[j + 1])
	{
		delimiter = args[j + 1];
		heredoc = read_heredoc(delimiter);
		parsed_struct[i].heredoc = heredoc;
	}
	else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
	{
		parsed_struct[i].input_file = ft_strdup(args[j + 1]);
	}
	else if (ft_strcmp(args[j], ">") == 0 && args[j + 1])
	{
		parsed_struct[i].output_file = ft_strdup(args[j + 1]);
	}
	remove_args(args, j, 2);
}


void	handle_variables_ph(char *line, char **prepared, int *i, int *j)
{
    char	var_name[1024];
printf ("line[*i]: %c\n", line[*i]);
    if (line[*i] == '$' && (*i == 0 || line[*i - 1] != '\\'))
    {
        (*i)++;
        get_var_name(line, i, var_name);
		if (*prepared != NULL)
        	*prepared = replace_var_value(var_name, *prepared, j);
    }
printf("PREPARED: %s\n", *prepared);
}

void	get_var_name(char *line, int *i, char *var_name)
{
	int	j;

	j = 0;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		var_name[j++] = line[*i];
		(*i)++;
	}
	var_name[j] = '\0';
printf ("var_name: %s\n", var_name);
}

char *replace_var_value(char *var_name, char *prepared, int *j)
{
    char *var_value;
    char *new_prepared;
    int before_var_len;
    int after_var_len;

    var_value = getenv(var_name);
    if (var_value != NULL && *j >= (int)(strlen(var_name) + 1) && prepared != NULL)
    {
        before_var_len = *j - strlen(var_name) - 1;
        after_var_len = strlen(prepared + *j);

        new_prepared = malloc(before_var_len + strlen(var_value) + after_var_len + 1);
        if (new_prepared == NULL)
        {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(1);
        }

        strncpy(new_prepared, prepared, before_var_len);
        new_prepared[before_var_len] = '\0'; // Ensure null termination

        strcpy(new_prepared + before_var_len, var_value);

        strcpy(new_prepared + before_var_len + strlen(var_value), prepared + *j);

        free(prepared);
        prepared = new_prepared;

        *j = before_var_len + strlen(var_value);
    }
    printf ("prepared: %s\n", prepared);
    return prepared;
}


// char *replace_var_value(char *var_name, char *prepared, int *j)
// {
//     char *var_value;
//     var_value = getenv(var_name);
//     if (var_value != NULL)
//     {
//         // Create a new string that will hold the replaced value
//         char *new_prepared = malloc(strlen(prepared) - strlen(var_name) - 1 + strlen(var_value) + 1);
//         if (new_prepared == NULL)
//         {
//             fprintf(stderr, "Failed to allocate memory\n");
//             exit(1);
//         }

//         // Copy the part of the prepared string before the variable
//         strncpy(new_prepared, prepared, *j - strlen(var_name) - 1);

//         // Copy the variable value to the new string
//         strcpy(new_prepared + *j - strlen(var_name) - 1, var_value);

//         // Copy the rest of the prepared string after the variable
//         strcpy(new_prepared + *j - strlen(var_name) - 1 + strlen(var_value), prepared + *j);

//         // Free the old prepared string and update the pointer
//         free(prepared);
//         prepared = new_prepared;

//         // Update the index to point to the end of the variable value
//         *j = *j - strlen(var_name) - 1 + strlen(var_value);
//     }
//     printf ("prepared: %s\n", prepared);
//     return prepared;
// }
