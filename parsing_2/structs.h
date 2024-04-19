/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:23:02 by demacinema        #+#    #+#             */
/*   Updated: 2024/04/19 15:07:15 by demacinema       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// STRUCT LIST - AFTER USE THE LIBFT ONE!!!!
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}			t_list;

// STRUCT DOUBLE LINKED LIST
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}			t_dlist;

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

#endif