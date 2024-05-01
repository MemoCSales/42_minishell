/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:22 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/04/02 13:10:23 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define MAX_CMD_LEN 1024
# define EXEC_ERROR 127

typedef struct s_main
{
	char	*cmd;
	char	*flags;
	char	**args;
	char	*input_file;
	char	*output_file;
	int		fd[2];
	pid_t	pid;
}			t_main;

typedef struct s_env
{
	char	**env_vars;
	int		status;
}			t_env;

// main
void		main_loop(t_env env_var, t_main *main_var);

// Functions for the buildins
int			builtins_no_output(char *cmd);
int			builtins_with_output(char *cmd);
int cd_builtin(t_env *env_vars, char *path);
int			pwd_builtin(void);
int			env_builtin(t_env *env_vars);
int			unset_builtin(t_env *env_vars, char *var_name);
int			find_index(t_env *env_vars, char *var_name);
int			export_builtin(t_env *env_vars, char *new_var);
int			is_valid_var_name(char *var);
int			check_duplicate(t_env *env_vars, char *new_var);
int			echo_builtin(t_main *main, t_env *env);
int			exit_builtin(t_main *main);
int			exec_builtin(t_env *env_vars, t_main *main);

// Environment variables
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);

// exec.c
int			execute_command(t_env *env, t_main *main);
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
int			parent_process(t_main *main, t_env *env, int i);
// redirections
int			check_for_redirect_output(t_main *main);
int			check_for_redirect_input(t_main *main);
void		handle_output_redirection(t_main *main, int i);
void		handle_input_redirection(t_main *main, int i);

// exec_utils.c
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
// void	pipe_redirection(t_main *main, t_env *env_vars, int i);
void		pipe_redirection(t_main *main, int i);
char		**build_exec_args(t_main *main, char **exec_args, int i);

// parsing
t_main		*parse_line(char *line);
int			count_cmds(char **cmds);
char		**copy_args(char **args);

// utils
void		cleanup_split(char **split);
void		free_main(t_main *main_var);
void		print_struct(t_main *main);

#endif