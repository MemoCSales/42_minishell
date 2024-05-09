/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./utils/color_code.h"
# include <assert.h> //to test parsing functions
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_CMD_LEN 1024
# define EXEC_ERROR 127
# define MAX_ARGS 100
# define MAX_ARG_LEN 1000

# define DEBUG 0

typedef struct s_main
{
	char	*cmd;
	// char	**flags;
	char	*flags;
	char	**args;
	char	*input_file;
	char	*output_file;
	char	*heredoc;
	char	*extra;
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
// int			cd_builtin(t_env *env_vars, char *path);
int			cd_builtin(t_env *env_vars, char *path, t_main *main);
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
void		ft_strcpy_memo(char *dst, char *src);

// Environment variables
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);

// echo.c
char	*ft_strremove(char *string, int c);

// exec.c
int			execute_command(t_env *env, t_main *main);
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
// int			parent_process(t_main *main, t_env *env, int i);
int			parent_process(t_main *main, t_env *env, int i, int pipe_created);
// redirections
int			check_for_redirect_output(t_main *main);
int			check_for_redirect_input(t_main *main);
void		handle_output_redirection(t_main *main, int i);
void		handle_input_redirection(t_main *main, int i);

// exec_utils.c
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
// void	pipe_redirection(t_main *main, t_env *env_vars, int i);
int			pipe_redirection(t_main *main, int i);
char		**build_exec_args(t_main *main, char **exec_args, int i);

// parsing
t_main		*parse_line(char *line);

// utils
void		cleanup_split(char **split);
void		free_main(t_main *main_var);
void		free_args(char **args); //due segfault when testing parsing

// parse_utils
t_main		*initialize_main(t_main *main_var, int num_commands);
int			ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dest, char *src, size_t n);
char		*insert_spaces(char *command);
void		ft_erase_quotes(char *tkn);
void		remove_args(char **args, int start_index, int num_args);
char		*read_heredoc(char *delimiter);
int			count_cmds(char **cmds);
char		**copy_args(char **args);
int			count_args(char **args);
char		*ft_strcat(char *dest, const char *src);
char		*read_quotes(char *delimiter);

// parse_utils_2
void		print_args(char **args);
void		print_struct(t_main *main_var, int i);
void		check_malloc(void *ptr);
int			check_redir(char **args, int j);
void		redirection(t_main *parsed_struct, char **args, int i, int j);

// parse_utils_3
char		*prepared_input(char *line);
char		**remove_start_quotes(char **args);

// parse_utils_4
int		in_quotes(char *line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */