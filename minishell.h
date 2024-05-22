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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>

# define MAX_CMD_LEN 1024
# define EXEC_ERROR 127
# define MAX_ARGS 100
# define MAX_ARG_LEN 1000

# define DEBUG 1

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
	pid_t	grandson_pid;
}			t_main;

typedef struct s_process_string_params
{
	int		i;
	int		j;
	int		start;
	char	quote_char;
	char	**res;
}			t_process_string_params;

typedef struct s_command_params
{
	char	*command;
	char	*changed;
	int		*i;
	int		*j;
	int		in_string;
}				t_command_params;

typedef struct s_env
{
	char	**env_vars;
	int		status;
}			t_env;

typedef struct s_exec
{
	t_main	*main;
	t_env	*env;
	int		i;
	char	**exec_args;
	char	*path_env;
	char	*path_cmd;
	int		heredoc_fd;
	int		pipe_created;
}			t_exec_context;

//main
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
int			export_builtin(t_env *env_vars, t_main *main, char *new_var);
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

int			builtins_no_output(char *cmd);
int			builtins_with_output(char *cmd);
int			env_builtin(t_env *env_vars);
int			exec_builtin(t_env *env_vars, t_main *main);

/*-----------------------PWD BUILTIN------------------------------*/
int			pwd_builtin(t_main *main);

/*-----------------------EXIT BUILTIN-----------------------------*/
int			exit_builtin(t_main *main);
int			ft_normal_exit(t_main *main);

/*-----------------------UNSET BUILTIN-----------------------------*/
int			unset_builtin(t_env *env_vars, char *var_name);
int			find_index(t_env *env_vars, char *var_name);

/*-----------------------ECHO BUILTIN-----------------------------*/
int			echo_builtin(t_main *main, t_env *env);

/*--------------------ENVIRONMENT VARIABLES FUNCTION--------------*/
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);
char		*ft_strdup_minishell(char *s1);

/*--------------------EXECUTION FUNCTIONS-------------------------*/
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
void		handle_file_redirection(t_main *main, int i, int heredoc_fd);
void		print_exec_args(char **exec_args);
int			handle_heredoc(t_main *main, int i);
void		handle_output_redirection(t_main *main, int i);
void		handle_input_redirection(t_main *main, int i);
int			parent_process(t_exec_context *context);
void		handle_child_process(t_exec_context *context);
void		handle_grandson_process(t_exec_context *context);
int			execute_command(t_env *env, t_main *main);
int			execute_with_commands(t_exec_context *context);
int			exec_without_cmds(t_exec_context *context);
int			execute_without_commands(t_exec_context *context);
void		initialize_context(t_exec_context *context);

/*--------------------GENERAL UTIL FUNCTIONS---------------------*/
void		error_messages(char *type);
void		print_open_fds(void);

/*--------------------SIGNALS FUNCTIONS--------------------------*/
void		siginit_handler(void);
void		sigquit_handler(void);
void		setup_signals(void);

// redirections
void		handle_output_redirection(t_main *main, int i);
void		handle_input_redirection(t_main *main, int i);

//exec_utils.c
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
//void	pipe_redirection(t_main *main, t_env *env_vars, int i);
int			pipe_redirection(t_main *main, int i);
char		**build_exec_args(t_main *main, char **exec_args, int i);

//utils/cleanup.c
void		cleanup_split(char **split);
void		free_main(t_main *main_var);
void		free_args(char **args);
void		free_and_nullify(void **ptr);
void		free_parsed_struct(t_main *parsed_struct, int num_commands);

//utils/cleanup_2.c
void		free_args_2(char ***args);

//parse.c
t_main		*parse_line(char *line, t_env *env_var);
t_main		*initialize_main(t_main *main_var, int num_commands);

//parse_utils
//1_args.c
char		**copy_args(char **args);
void		remove_args(char **args, int start_index, int num_args);
void		remove_args_first_last_quotes(char *arg);
int			ft_strequ(char const *s1, char const *s2);

//2_input_handling.c
char		*prepare_line(char *line, char ***ph_strings, t_env *env_var);
void		handle_input(char *line, char *prepared);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
// void		handle_others(char *line, char *prepared, int *i, int *j);

//3_redirection_and_variables.c
int			check_redir(char **args, int j);
void		redirection(t_main *parsed_struct, char **args, int i, int j);
void		handle_variables_ph(char *line, char **prepared, int *i, int *j);
void		get_var_name(char *line, int *i, char *var_name);
char		*replace_var_value(char *var_name, char *prepared, int *j);

//4_quotes.c
void		handle_quotes(char *line, int *i, int *in_quotes);
int			in_quotes(char *line);
void		clean_quotes(char **args);
void		erase_quotes(char *command);
// void		remove_double_quotes(char *str);

//5_command_processing.c
char		*process_command_string(char *command);
int			word_count_mini(const char *str, char chr);
void		process_string(const char *s, char c, \
			t_process_string_params *params);
char		**ft_split_args(const char *s, char c);
// char	*insert_spaces(char *command);
// void	process_command(char *command, char *changed);
// void		insert_spaces_in_command(char *command, \
// 			char *changed, int *i, int *j);

//6_pipe_and_redirection.c
char		*read_quotes(char *delimiter, char *line);
char		*check_closed_quotes(char *line);
char		*read_heredoc(char *delimiter);
void		create_pipe(t_main *command, int i, int num_commands);
void		handle_redirections(t_main *parsed_struct, char **args, int i);

//7_string_manipulation.c
int			ft_strcpy(char *dst, const char *src); //COPY SRC TO DST
char		*ft_strncpy(char *dest, char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strswap(char *str, char *substr, char *replacement);
char		*ft_strnjoin(char const *s1, char const *s2, size_t n);
// char		*ft_strndup(const char *s, size_t n);

//8_is_and_prints.c
int			is_whitespace(char c); //CHECK IF CHAR IS WHITESPACE
int			is_escaped(char *line, int index); //CHECK IF CHAR IS ESCAPED
int			is_char_in_quotes(char *line, int index);
void		print_args(char **args); //PRINT **ARGS
void		print_struct(t_main *main_var, int i); //PRINT STRUCT t_main
// char	*handling(char *command);
// char	*pre_handle_quotes(char *command);
// char	*pre_handle_escaped_quotes(char *command);
// void	copy_increment(char *prepared, const char *line, int *i, int *j);

//9_checkers_and_counters.c
void		check_malloc(void *ptr);
void		check_flags(t_main *command, char **args);
int			check_delimiter(char *delimiter);
int			count_elements(char **elements);
void		print_ph_strings(char ***ph_strings);

//10_placeholder_1.c
char		*remove_backslashes(const char *str);
char		**allocate_strings(const char *line, int *num_strings);
const char	*find_next_string(const char *start, \
			const char *line, const char **end);
char		**extract_strings(const char *line, int *numStrings);
void		process_string_placehoder(char **strings, \
			const char *start, const char *end, int occurrence);
char		**extract_strings(const char *line, int *numStrings);
// char		*generate_placeholder(int occurrence, char quote_type);
// // char		*generate_placeholder(int occurrence);
// void		replace_with_placeholder(char *line);
// // int			count_occurrences(const char *str, char c);
// int			count_occurrences(const char *str, char c, char d);
// char		*ft_strsub(char const *s, unsigned int start, size_t len);
// void		process_string_extract(const char **start, \
// 			char **strings, int *occurrence);
// const char	*find_start(const char *start);

//11_placeholder_2.c
void		placeholder(char *line, char ***ph_strings);
void		replace_placeholder_sub(char **str, \
			char *placeholder, char *replacement);
void		handle_psi(char **str, char ***ph_strings, int *i);
void		handle_psi_lower(char **str, char ***ph_strings, int *i);
void		reverse_placeholders(char **str, char ***ph_strings);
// void		replace_single_placeholder(char **command, \
// 			char *placeholder, char *replacement);
// void		replace_placeholder_sub(char **str, char *placeholder, \
// 			char *replacement);
// void		reverse_placeholders(char **command, char ***ph_strings);
// void		reverse_placeholders_in_struct(t_main *command, char ***ph_strings);
// void		handle_variables_ph(char *line, \
// 			char **prepared, int *i, int *j);
// void	replace_placeholders(char **command, char ***ph_strings);

//12_placeholder_3.c
char		*generate_placeholder(int occurrence, char quote_type);
void		replace_with_placeholder(char *line);
int			count_occurrences(const char *str, char c, char d);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
void		reverse_placeholders_in_struct(t_main *command, char ***ph_strings);

//13_string_manipulation_2.c
char		*ft_strndup(const char *s, size_t n);

//14_insert_spaces.c
void		insert_spaces_in_command(char *command, \
			char *changed, int *i, int *j);
void		insert_spaces_and_duplicate_command(char *changed, \
			int *j, char *command, int *i);

//parse_test
// void	append_var_value(char **prepared, int *j, char *var_value)
// void	handle_variables(char *line, char *prepared, int *i, int *j)
// void	handle_quotes(char *line, int *i, int *in_quotes)
// void	handle_others(char *line, char *prepared, int *i, int *j)
// void	handle_input(char *line, char *prepared)
// char	*prepare_line(char *line);
// int	calculate_total_size(char *line);
//could be done to calculate size of malloc

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