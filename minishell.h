/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demacinema <demacinema@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2024/05/07 20:54:59 by demacinema       ###   ########.fr       */
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
# include <stdio.h> //to test parsing functions
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_CMD_LEN 1024
# define EXEC_ERROR 127

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
	char	*current_dir;
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
/*------------------------CD BUILTIN-----------------------------*/
int			cd_builtin(t_env *env_vars, char *path, t_main *main);
char		*create_new_var(char *var_name, char *new_value);
void		find_and_replace_var(t_env *env, char *var_name, char *new_var);
void		update_env_var(t_env *env, char *var_name, char *new_value);
char		*get_path(t_main *main, char *path);
int			change_directory(t_main *main, char *path);
void		update_env(t_env *env_vars, char *prev_dir, t_main *main);
void		cd_error_check(char *path);
void		ft_strcpy_memo(char *dst, char *src);

/*--------------------EXPORT BUILTIN-----------------------------*/
int			export_builtin(t_env *env_vars, char *new_var);
int			get_name_length(char *new_var);
int			replace_env_var(t_env *env, char *new_var, int i);
int			check_duplicate(t_env *env_vars, char *new_var);
void		print_invalid_identifier(char *var);
int			is_valid_first_char(char *var);
int			is_valid_remaining_chars(char *var);
int			ft_isupper(int c);
int			is_all_uppercase(char *var);
int			is_valid_var_name(char *var);
void		print_env_vars(t_env *env_vars);
int			validate_new_var(t_env *env_vars, char *new_var);
char		**allocate_new_env_vars(t_env *env_vars);
void		copy_env_vars(t_env *env_vars, char **new_env_vars);
int			add_new_var(char *new_var, char **new_env_vars, int i);

/*-----------------------PWD BUILTIN------------------------------*/
int			pwd_builtin(t_main *main);

/*-----------------------EXIT BUILTIN-----------------------------*/
int			exit_builtin(t_main *main);
int			ft_normal_exit(t_main *main);

/*-----------------------UNSET BUILTIN-----------------------------*/
int			unset_builtin(t_env *env_vars, char *var_name);
int			find_index(t_env *env_vars, char *var_name);

int			builtins_no_output(char *cmd);
int			builtins_with_output(char *cmd);
int			env_builtin(t_env *env_vars);
int			exec_builtin(t_env *env_vars, t_main *main);

/*-----------------------ECHO BUILTIN-----------------------------*/
int			echo_builtin(t_main *main, t_env *env);

/*--------------------ENVIRONMENT VARIABLES FUNCTION--------------*/
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);
char		*ft_strdup_minishell(char *s1);

/*--------------------EXECUTION FUNCTIONS-------------------------*/
int			execute_command(t_env *env, t_main *main);
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
// int			parent_process(t_main *main, t_env *env, int i);
int			parent_process(t_main *main, t_env *env, int i, int pipe_created);
void		handle_file_redirection(t_main *main, int i, int heredoc_fd);
int			exec_without_cmds(t_main *main, t_env *env, int i);


/*--------------------GENERAL UTIL FUNCTIONS---------------------*/
void		error_messages(char *type);

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
void		old_print_struct(t_main *main_var, int num_commands);
void	free_args(char **args); // due segfault when testing parsing

// parse_utils
t_main		*initialize_main(t_main *main_var, int num_commands);
int			ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dest, char *src, size_t n);
void		test_parser(void);
char		*insert_spaces(char *command);
void		ft_erase_quotes(char *tkn);
void		remove_args(char **args, int start_index, int num_args);
char		*read_heredoc(char *delimiter);
int			count_cmds(char **cmds);
char		**copy_args(char **args);
int			count_args(char **args);

// parse_utils_2
void		print_args(char **args);
void		print_struct(t_main *main_var, int i);
void		check_malloc(void *ptr);
int			check_redir(char **args, int j);
t_main		*redirection(t_main *parsed_struct, char **args, int i, int j);

void		print_open_fds(void);

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