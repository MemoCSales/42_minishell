/* ************************************************************************** */
/*                                                                            */
/*   15_handle_variables_1.c        ψΨ MiniℍΞLL Ψψ        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_variables(char *line, t_env *env_var)
{
	t_handle_vars	h_vars;

	h_vars = start_h_vars(&h_vars, line);
	line = change_unquoted_dollar_signs(line);
	if (ft_strchr(line, '$'))
	{
		h_vars.quotes = is_char_in_quotes(line, ft_strchr(line, '$') - line);
		if (h_vars.quotes == 0)
			h_vars = quotes_zero(&h_vars, line);
	}
	h_vars.i = 0;
	h_vars.quotes = ft_strchr(line, '$') - line;
	if (h_vars.quotes >= 0)
		h_vars.quotes = is_char_in_quotes(line, h_vars.quotes);
	while (line[h_vars.i] != '\0')
		h_vars = if_conditions(&h_vars, line, env_var);
	h_vars.result[h_vars.j] = '\0';
	return (h_vars.result);
}

t_handle_vars	start_h_vars(t_handle_vars *h_vars, char *line)
{
	h_vars->i = 0;
	h_vars->j = 0;
	h_vars->var_start = NULL;
	h_vars->var_end = NULL;
	h_vars->status = NULL;
	h_vars->size = 0;
	h_vars->result = malloc(strlen(line) * 200);
	h_vars->quotes = 0;
	return (*h_vars);
}
