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

// #include "../main.h"

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

// UTILS - parsing/parse_utils.c
void	ft_jump_spaces(const char *str, int *position);
void	ft_jump_letters(const char *str, int *position);
void	ft_jump_quotes (const char *str, int *position);
void	ft_erase_quotes(char *tkn);
char	*ft_search_outside_quotes(char *str, char *needle);

// UTILS TABLES AND DELIMITERS - parsing/parse_utils.c
char *get_cmdlist_separator(const char *str, int *position);

// CHECKERS - parsing/checkers.c
int		ft_isdigit(char c);
int		ft_isenv_or_path(char c);
int		ft_isquote(char c);
int		ft_isspace(char c);

int		ft_istoken_separator(char c);
int		ft_iscmd_separator(char c);
int ft_iscmdlist_separator(const char *str);

// MINI LIBFTS FUNCTIONS - parsing/checkers.c
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *data);

char	*ft_strncpy(char *dest, char *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strcpy(char *dst, const char *src);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(const char *s);

void	*ft_calloc(size_t count, size_t size);

// PARSER - parsing/parser.c
char		*set_token(const char *string, int *position);
t_redir		*set_redir(const char *string, int *position);
t_cmd		*set_cmd(const char *string, int *position);
t_cmdlist	*set_cmdlist(const char *string, int *position);
t_ast	*set_ast(const char *string);

#endif