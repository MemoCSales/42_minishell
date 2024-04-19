/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:27:08 by demacinema        #+#    #+#             */
/*   Updated: 2024/04/19 14:57:02 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/// JUMP SPACES
/// @brief - jump spaces in the string
/// @param str - string to jump spaces from
/// @param position - actual position in the string
void	ft_jump_spaces(const char *str, int *position)
{
	while (str[*position] && ft_isspace(str[*position])) // while is not the end of the string, and the character is a space
		(*position)++; // increment the position
}

/// JUMP LETTERS
/// @brief - jump letters in the string, and also if is an environment variable ($) or absolute path (/)
/// @param str - string to jump letters from
/// @param position - actual position in the string
void	ft_jump_letters(const char *str, int *position)
{
	if (ft_isenv_or_path(str[*position])) // if the character is $ or /, increment the position
		(*position)++;
	while (str[*position] && !ft_isquote(str[*position]) && !ft_isenv_or_path(str[*position])) // while is not the end of the string, and the character is not a quote, and is not $ or /
		(*position)++; // increment the position
}

/// JUMP QUOTES
/// @brief - called when a quote is found, jump to the next position after the closed quote
/// @param str - string with quotes
/// @param position - actual position in the string
void	ft_jump_quotes (const char *str, int *position)// move the position, jumping quotes inside string
{
	int	double_q_flag;
	int	single_q_flag;

	double_q_flag = 0;
	single_q_flag = 0;
	while (str[*position]) // this function will be called only if a quote is found, we need to see if single or double
	{
	if (str[*position] == '"' && single_q_flag == 0)
		double_q_flag = !double_q_flag;// invert flag, we are inside double quotes
	else if (str[*position] == '\'' && double_q_flag == 0)
		single_q_flag = !single_q_flag;// invert flag, we are inside single quotes
	(*position)++; // with *, as we are passing the address of the variable, so we need to dereference it.
					// it is inside parenthesis because we want to increment the VALUE of the variable, not the address
	if (!double_q_flag && !single_q_flag)// if they are both false now, as at the beginning we had found a quote, we
		break;	 // exited the seconde quote, so we can break the loop (with one position increment, next char after quote)
	}			// ONLY EXITS WITH BREAK, IF ANOTHER QUOTE OF THE SAME TYPE IS FOUND. IF NOT, GOES UNTIL THE END OF THE STRING
}

/// ERASE QUOTES
/// @brief - erase USELESS quotes from the tokens, matching quotes are replaced by the rest of the string (without the quote)
/// @param tkn - token extracted from input string

void	ft_erase_quotes(char *tkn)
{
	int i;
	int	double_q_flag;
	int	single_q_flag;
	
	i = 0;
	double_q_flag = 0;
	single_q_flag = 0;
	
	while (tkn[i])
	{
		if (tkn[i] == '"' && single_q_flag == 0)
		{
			double_q_flag = !double_q_flag;
			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
			continue;
		}
		else if (tkn[i] == '\'' && double_q_flag == 0)
		{
			single_q_flag = !single_q_flag;
			ft_strcpy(&tkn[i], (const char *)&tkn[i + 1]);
			continue;
		}
		i++;
	}
}

/// SEARCH OUTSIDE QUOTES
/// @brief - search for the required text, but only outside quotes that are inside the string
///			if the quote found is not closed, it will search fot the needle only until the first quote
/// @param str - string from where to search
/// @param needle - text to search
/// @return - address where the needle is (will be the whole string after first match)
char	*ft_search_outside_quotes(char *str, char *needle)
{
	int i;

	i = 0;
	
	if (!(*needle)) // if the needle is empty, return the string
		return (str);
		
	while (str[i]) // loop through the string
	{
		if (ft_isquote(str[i])) //(str[i] == '"' || str[i] == '\'') // if character is quote, jump to the next position after the closed quote, if NOT closed, goes until the end of the string
			ft_jump_quotes(str, &i); // update the *position to keep parsing
		if (!ft_strncmp(&str[i], needle, ft_strlen(needle))) // compare the string from the position i with the needle
							// the ft_strncmp function compares the strings, and returns 0 if they are the same. if they
							// are not the same, it returns the difference between the first two different characters

			return (&str[i]);
		if (str[i])
			i++;
	}
	return (0);
}

/// GET CMDLIST SEPARATOR
/// @brief - get the separator between commands in the command list and advance the position in the string
/// @param str - string to search for the separator
/// @param position - actual position in the string
/// @return - the separator found ('\0', ';', '&&' or '||')
char *get_cmdlist_separator(const char *str, int *position)
{
	char *separator;
	
	separator = 0;
	if (str[*position] == '\0')
		separator = ft_strdup("");
	else if (str[*position] == ';')
	    separator = ft_strdup(";");
	else if (!ft_strncmp((char *)&str[*position], "&&", 2))
		separator = ft_strdup("&&");
	else if (!ft_strncmp((char *)&str[*position], "||", 2))
		separator = ft_strdup("||");
	if (!separator)
		return (0); // QUIT PROGRAM // LATER QUIT PROGRAM CORRECTLY WITH EXIT PGM FUNCTION
	(*position) += ft_strlen(separator); // increment the size of the separator
	return (separator);
}