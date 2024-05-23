/* ************************************************************************** */
/*                                                                            */
/*   15_handle_variables.c          ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_handle_vars	start_h_vars(t_handle_vars *h_vars, char *line)
{
	h_vars->i = 0;
	h_vars->j = 0;
	h_vars->var_start = NULL;
	h_vars->var_end = NULL;
	h_vars->status = NULL;
	h_vars->size = 0;
	h_vars->result = malloc(strlen(line) * 200);
	line = change_unquoted_dollar_signs(line);
	h_vars->quotes = 0;
	return (*h_vars);
}

// char	*handle_variables(char *line, t_env *env_var)
// {
// 	t_handle_vars	h_vars;

// 	h_vars = start_h_vars(&h_vars, line);
// 	if (ft_strchr(line, '$'))
// 	{
// 		h_vars.quotes = is_char_in_quotes(line, ft_strchr(line, '$') - line);
// 		if (h_vars.quotes == 0)
// 		{
// 			h_vars.var_start = &line[ft_strchr(line, '$') - line];
// 			h_vars.var_end = h_vars.var_start;
// 			h_vars.var_end++;
// 			while (ft_isalnum(*h_vars.var_end) || *h_vars.var_end == '_')
// 				h_vars.var_end++;

// 			// h_vars.var_name[h_vars.var_end - (h_vars.var_start + 1)];
// 			// ft_strncpy(h_vars.var_name, h_vars.var_start + 1, \
// 			// 	((h_vars.var_end) - (h_vars.var_start)));
// 			// h_vars.var_name[h_vars.var_end - h_vars.var_start] = '\0';

// 			h_vars.size = (h_vars.var_end - (h_vars.var_start + 1));
// 			h_vars.var_name = malloc(h_vars.size);
// 			check_malloc(h_vars.var_name);
// 			ft_strncpy(h_vars.var_name, h_vars.var_start + 1, \
// 				((h_vars.var_end) - (h_vars.var_start)));
// 			h_vars.var_name[h_vars.var_end - h_vars.var_start] = '\0';

// 			h_vars.var_value = getenv(h_vars.var_name);
// 			if (h_vars.var_value != NULL)
// 			{
// 				ft_strcpy(&h_vars.result[h_vars.j], h_vars.var_value);
// 				h_vars.j += strlen(h_vars.var_value);
// 			}
// 			h_vars.i = h_vars.var_end - line;
// 			h_vars.size = 0;
// 			free(h_vars.var_name);
// 		}
// 	}
// 	h_vars.i = 0;
// 	h_vars.quotes = ft_strchr(line, '$') - line;
// 	if (h_vars.quotes >= 0)
// 		h_vars.quotes = is_char_in_quotes(line, h_vars.quotes);
// 	while (line[h_vars.i] != '\0')
// 	{
// 		if ((line[h_vars.i] == '$' && (h_vars.i == 0
// 					|| line[h_vars.i - 1] != '\\')) && (h_vars.quotes == 2)
// 			&& (line[h_vars.i + 1] != ' ') && (line [h_vars.i + 1] != '?')
// 			&& (line[h_vars.i + 1] != '\'' && line[h_vars.i + 1] != '\"'))
// 		{
// 			h_vars.var_start = &line[h_vars.i + 1];
// 			h_vars.var_end = h_vars.var_start;
// 			while (ft_isalnum(*h_vars.var_end) || *h_vars.var_end == '_')
// 				h_vars.var_end++;

// 			// h_vars.var_name[h_vars.var_end - h_vars.var_start + 1];
// 			// ft_strncpy(h_vars.var_name, h_vars.var_start, \
// 			// 	(h_vars.var_end - h_vars.var_start));
// 			// h_vars.var_name[h_vars.var_end - h_vars.var_start] = '\0';

// 			h_vars.size = (h_vars.var_end - (h_vars.var_start + 1));
// 			h_vars.var_name = malloc(h_vars.size);
// 			check_malloc(h_vars.var_name);
// 			ft_strncpy(h_vars.var_name, h_vars.var_start + 1, \
// 				((h_vars.var_end) - (h_vars.var_start)));
// 			h_vars.var_name[h_vars.var_end - h_vars.var_start] = '\0';

// 			h_vars.var_value = getenv(h_vars.var_name);
// 			if (h_vars.var_value != NULL)
// 			{
// 				ft_strcpy(&h_vars.result[h_vars.j], h_vars.var_value);
// 				h_vars.j += ft_strlen(h_vars.var_value);
// 			}
// 			h_vars.i = h_vars.var_end - line;
// 			h_vars.size = 0;
// 			free(h_vars.var_name);
// 		}
// 		else if (line[h_vars.i] == '$' && line[h_vars.i + 1] == '?'
// 			&& h_vars.quotes != 1 && line[h_vars.i - 1] != '\\')
// 		{
// 			h_vars.status = ft_itoa(env_var->status);
// 			ft_strcpy(&h_vars.result[h_vars.j], h_vars.status);
// 			h_vars.j += ft_strlen(h_vars.status);
// 			h_vars.i += 2;
// 		}
// 		else
// 		{
// 			if (line[h_vars.i] == '\\' && line[h_vars.i + 1] == '$')
// 			{
// 				h_vars.result[h_vars.j++] = '$';
// 				h_vars.i += 2;
// 			}
// 			else
// 				h_vars.result[h_vars.j++] = line[h_vars.i++];
// 		}
// 	}
// 	h_vars.result[h_vars.j] = '\0';
// 	return (h_vars.result);
// }

//ANTIGA ANTES DE NORMETTIZAR
char	*handle_variables(char *line, t_env *env_var)
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
	line = change_unquoted_dollar_signs(line);
	quotes = 0;
	if (ft_strchr(line, '$'))
	{
		quotes = is_char_in_quotes(line, ft_strchr(line, '$') - line);
		if (quotes == 0)
		{
			env_var_start = &line[ft_strchr(line, '$') - line];
			env_var_end = env_var_start;
			env_var_end++;
			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
				env_var_end++;
			char	env_var_name[env_var_end - (env_var_start + 1)];
			ft_strncpy(env_var_name, env_var_start + 1, \
				((env_var_end) - (env_var_start)));
			env_var_name[env_var_end - env_var_start] = '\0';
			char	*env_var_value = getenv(env_var_name);
			if (env_var_value != NULL)
			{
				strcpy(&result[j], env_var_value);
				j += strlen(env_var_value);
			}
			i = env_var_end - line;
		}
	}
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
			env_var_start = &line[i + 1];
			env_var_end = env_var_start;
			while (ft_isalnum(*env_var_end) || *env_var_end == '_')
				env_var_end++;
			char	env_var_name[env_var_end - env_var_start + 1];
			ft_strncpy(env_var_name, env_var_start, \
				(env_var_end - env_var_start));
			env_var_name[env_var_end - env_var_start] = '\0';
			char	*env_var_value = getenv(env_var_name);
			if (env_var_value != NULL)
			{
				strcpy(&result[j], env_var_value);
				j += strlen(env_var_value);
			}
			i = env_var_end - line;
		}
		else if (line[i] == '$' && line[i + 1] == '?'
			&& quotes != 1 && line[i - 1] != '\\')
		{
			status = ft_itoa(env_var->status);
			ft_strcpy(&result[j], status);
			j += ft_strlen(status);
			i += 2;
		}
		else
		{
			if (line[i] == '\\' && line[i + 1] == '$')
			{
				result[j++] = '$';
				i += 2;
			}
			else
				result[j++] = line[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
