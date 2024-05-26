/* ************************************************************************** */
/*                                                                            */
/*   16_handle_variables_2.c        ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_handle_vars	quotes_zero(t_handle_vars *h_vars, char *line, t_env *env_var)
{
	h_vars->var_start = &line[ft_strchr(line, '$') - line];
	h_vars->var_end = h_vars->var_start;
	h_vars->var_end++;
	while (ft_isalnum(*h_vars->var_end) || *h_vars->var_end == '_')
		h_vars->var_end++;
	h_vars->size = (h_vars->var_end - (h_vars->var_start + 1));
	h_vars->var_name = malloc(h_vars->size);
	check_malloc(h_vars->var_name);
	ft_strncpy(h_vars->var_name, h_vars->var_start + 1, \
		((h_vars->var_end) - (h_vars->var_start)));
	h_vars->var_name[h_vars->var_end - h_vars->var_start] = '\0';
	h_vars->var_value = get_env_var(env_var, h_vars->var_name);
	if (h_vars->var_value != NULL)
	{
		ft_strcpy(&h_vars->result[h_vars->j], h_vars->var_value);
		h_vars->j += ft_strlen(h_vars->var_value);
	}
	h_vars->i = h_vars->var_end - line;
	h_vars->size = 0;
	free(h_vars->var_name);
	return (*h_vars);
}

t_handle_vars	quotes_double(t_handle_vars *h_vars, char *line, t_env *env_var)
{
	h_vars->var_start = &line[h_vars->i + 1];
	h_vars->var_end = h_vars->var_start;
	while (ft_isalnum(*h_vars->var_end) || *h_vars->var_end == '_')
		h_vars->var_end++;
	h_vars->size = (h_vars->var_end - (h_vars->var_start + 1));
	h_vars->var_name = malloc(h_vars->size);
	check_malloc(h_vars->var_name);
	ft_strncpy(h_vars->var_name, h_vars->var_start, \
		((h_vars->var_end) - (h_vars->var_start)));
	h_vars->var_name[h_vars->var_end - h_vars->var_start] = '\0';
	h_vars->var_value = get_env_var(env_var, h_vars->var_name);
	if (h_vars->var_value != NULL)
	{
		ft_strcpy(&h_vars->result[h_vars->j], h_vars->var_value);
		h_vars->j += ft_strlen(h_vars->var_value);
	}
	h_vars->i = h_vars->var_end - line;
	h_vars->size = 0;
	free(h_vars->var_name);
	return (*h_vars);
}

t_handle_vars	dollar_question(t_handle_vars *h_vars, t_env *env_var)
{
	h_vars->status = ft_itoa(env_var->status);
	ft_strcpy(&h_vars->result[h_vars->j], h_vars->status);
	h_vars->j += ft_strlen(h_vars->status);
	h_vars->i += 2;
	return (*h_vars);
}

t_handle_vars	escaped_dollar(t_handle_vars *h_vars, char *line)
{
	if (line[h_vars->i] == '\\' && line[h_vars->i + 1] == '$')
	{
		h_vars->result[h_vars->j++] = '$';
		h_vars->i += 2;
	}
	else
		h_vars->result[h_vars->j++] = line[h_vars->i++];
	return (*h_vars);
}

t_handle_vars	if_conditions(t_handle_vars *h_vars, char *line, t_env *env_var)
{
	t_handle_vars	h_vars_sub;

	if ((line[h_vars->i] == '$' && (h_vars->i == 0
				|| line[h_vars->i - 1] != '\\')) && (h_vars->quotes == 2)
		&& (line[h_vars->i + 1] != ' ') && (line [h_vars->i + 1] != '?')
		&& (line[h_vars->i + 1] != '\'' && line[h_vars->i + 1] != '\"'))
		h_vars_sub = quotes_double(h_vars, line, env_var);
	else if (line[h_vars->i] == '$' && line[h_vars->i + 1] == '?'
		&& h_vars->quotes != 1 && line[h_vars->i - 1] != '\\')
		h_vars_sub = dollar_question(h_vars, env_var);
	else
		h_vars_sub = escaped_dollar(h_vars, line);
	h_vars->i = h_vars_sub.i;
	return (*h_vars);
}
