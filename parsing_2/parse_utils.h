/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

// STRUCT FOR ALL THE COMMAND LISTS
typedef struct s_ast
{
	t_list		*cmdlist;
}			t_ast;

// STRUCT FOR EACH COMMAND LIST
typedef struct s_cmdlist
{
	t_list		*commands;
	t_list      *pids;
	char		*separator;
	int			nbr_commands;
	int			**pipes;
	int         return_value;
}			t_cmdlist;

// STRUCT FOR EACH COMMAND
typedef struct s_cmd
{
	t_list		*tokens;
	t_list      *redirs;
}			t_cmd;

// STRUCT FOR REDIRECTIONS
typedef struct s_redir
{
	char		*direction;
	char		type[3];
}			t_redir;

// UTILS - parsing/parse_utils.c
void	ft_jump_spaces(const char *str, int *position);
void	ft_jump_letters(const char *str, int *position);
void	ft_jump_quotes (const char *str, int *position);
void	ft_erase_quotes(char *tkn);
char	*ft_search_outside_quotes(char *str, char *needle);
int 	ft_isspace(char c);
char	*ft_strncpy(char *dest, char *src, size_t n);

// UTILS TABLES AND DELIMITERS - parsing/parse_utils.c
char *get_cmdlist_separator(const char *str, int *position);

// CHECKERS - parsing/checkers.c
int		ft_isenv_or_path(char c);
int		ft_isquote(char c);
int		ft_istoken_separator(char c);
int		ft_iscmd_separator(char c);
int ft_iscmdlist_separator(const char *str);

// PARSER - parsing/parser.c
char		*set_token(const char *string, int *position);
t_redir		*set_redir(const char *string, int *position);
t_cmd		*set_cmd(const char *string, int *position);
t_cmdlist	*set_cmdlist(const char *string, int *position);
t_ast		*set_ast(const char *string);

// OTHER FUNCTIONS - parsing/checkers.c
int		ft_strcpy(char *dst, const char *src);

#endif