/* ************************************************************************** */
/*                                                                            */
/*   5_command_processing.c     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*process_command_string(char *command)
{
	int		i;
	int		j;
	char	*changed;

	i = 0;
	j = 0;
	changed = malloc(strlen(command) * 2);
	check_malloc(changed);
	if (!command)
	{
		ft_putstr_fd("Error: No command specified\n", 2);
		exit (1);
	}
	while (command[i])
	{
		insert_spaces_in_command(command, changed, &i, &j);
	}
	changed[j] = '\0';
	erase_quotes(changed);
	return (changed);
}

void	insert_spaces_in_command(char *command, char *changed, int *i, int *j)
{
	int	in_string;

	in_string = 0;
	if (command[*i] == '"')
		in_string = !in_string;
	if (!in_string && (command[*i] == '>' || command[*i] == '<')
		&& command[*i + 1] != ' ' && command[*i + 1] != command[*i])
	{
		changed[(*j)++] = ' ';
		changed[(*j)++] = command[*i];
		changed[(*j)++] = ' ';
	}
	else if (!in_string && command[*i] == command[*i + 1]
		&& command[*i + 2] != ' ' && command[*i] == '>'
		&& command[*i] == '<')
	{
		changed[(*j)++] = ' ';
		changed[(*j)++] = command[*i];
		changed[(*j)++] = command[*i];
		(*i)++;
		changed[(*j)++] = ' ';
	}
	else
		changed[(*j)++] = command[*i];
	(*i)++;
}

int	word_count_mini(const char *str, char chr)
{
	size_t	word;
	size_t	i;

	if (!str)
		return (0);
	word = 0;
	i = 0;
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == chr) && str[i] != chr)
			word++;
		i++;
	}
	return (word);
}

void	process_string(const char *s, char c, t_process_string_params *params)
{
	while (s[params->i] != '\0' && !(s[params->i] == c
			&& params->quote_char == 0))
	{
		if ((s[params->i] == '"' || s[params->i] == '\'')
			&& (params->i == 0 || s[params->i - 1] != '\\'))
		{
			if (params->quote_char == 0)
				params->quote_char = s[params->i];
			else if (params->quote_char == s[params->i])
				params->quote_char = 0;
			params->i++;
		}
		if (params->i > params->start)
			params->res[params->j++]
				= ft_substr(s, params->start, params->i - params->start);
		while (s[params->i] == c)
			params->i++;
	}
}

char	**ft_split_args(const char *s, char c)
{
	char						**res;
	t_process_string_params		params;

	params.i = 0;
	params.j = 0;
	params.start = 0;
	params.quote_char = 0;
	res = (char **)malloc(sizeof(char *) * (word_count_mini(s, c) + 1));
	if (!res || !s)
		return (NULL);
	params.res = res;
	while (s[params.i] != '\0')
	{
		params.start = params.i;
		params.quote_char = 0;
		process_string(s, c, &params);
	}
	params.res[params.j] = NULL;
	return (params.res);
}

//ANTIGA, SUBSTITUIDA PELAS 3 ACIMA
// char	**ft_split_args(const char *s, char c)
// {
// 	char	**res;
// 	int		i;
// 	int		j;
// 	int		start;
// 	char	quote_char;

// 	i = 0;
// 	j = 0;
// 	res = (char **)malloc(sizeof(char *) * (word_count_mini(s, c) + 1));
// 	if (!res || !s)
// 		return (NULL);
// 	while (s[i] != '\0')
// 	{
// 		start = i;
// 		quote_char = 0;
// 		while (s[i] != '\0' && !(s[i] == c && quote_char == 0))
// 		{
// 			if ((s[i] == '"' || s[i] == '\'') && (i == 0 || s[i - 1] != '\\'))
// 			{
// 				if (quote_char == 0)
// 					quote_char = s[i];
// 				else if (quote_char == s[i])
// 					quote_char = 0;
// 				i++;
// 			}
// 			if (i > start)
// 				res[j++] = ft_substr(s, start, i - start);
// 			while (s[i] == c)
// 				i++;
// 		}
// 		res[j] = NULL;
// 		return (res);
// 	}
// }

//MAIS ANTIGA
// char	**ft_split_args(const char *s, char c)
// {
// 	char	**res;
// 	int		i;
// 	int		j;
// 	int		start;
// 	char	quote_char;

// 	i = 0;
// 	j = 0;
// 	res = (char **)malloc(sizeof(char *) * (word_count_mini(s, c) + 1));
// 	if (!res || !s)
// 		return (NULL);
// 	while (s[i] != '\0')
// 	{
// 		while (s[i] == c)
// 			i++;
// 		start = i;
// 		quote_char = 0; // No quote character at the start
// 		while (s[i] != '\0')
// 		{
// 			if (s[i] == c && quote_char == 0)
// 				break;
// 			if ((s[i] == '"' || s[i] == '\'') && (i == 0 || s[i - 1] != '\\'))
// 			{
// 				if (quote_char == 0)
// 					quote_char = s[i]; // Start of quoted string
// 				else if (quote_char == s[i])
// 					quote_char = 0; // End of quoted string
// 			}
// 			i++;
// 		}
// 		if (i > start)
// 			res[j++] = ft_substr(s, start, i - start);
// 	}
// 	res[j] = NULL;
// 	return (res);
// }

// char	*insert_spaces(char *command)
// {
// 	char	*changed;

// 	if (!command)
// 	{
// 		ft_putstr_fd("Error: No command specified\n", 2);
// 		exit (1);
// 	}
// 	changed = malloc(strlen(command) * 5 + 1);
// 	check_malloc(changed);
// 	process_command(command, changed);
// 	erase_quotes(changed);
// 	return (changed);
// }

// void	process_command(char *command, char *changed)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (command[i])
// 	{
// 		insert_spaces_in_command(command, changed, &i, &j);
// 	}
// 	changed[j] = '\0';
// }