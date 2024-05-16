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
	int		fd[2];
	pid_t	pid;
}			t_main;

typedef struct s_process_string_params
{
	int		i;
	int		j;
	int		start;
	char	quote_char;
	char	**res;
}			t_process_string_params;

typedef struct s_env
{
	char	**env_vars;
	int		status;
}			t_env;

//main
void	main_loop(t_env env_var, t_main *main_var);

//Functions for the buildins
int		builtins_no_output(char *cmd);
int		builtins_with_output(char *cmd);
//int			cd_builtin(t_env *env_vars, char *path);
int		cd_builtin(t_env *env_vars, char *path, t_main *main);
int		pwd_builtin(void);
int		env_builtin(t_env *env_vars);
int		unset_builtin(t_env *env_vars, char *var_name);
int		find_index(t_env *env_vars, char *var_name);
int		export_builtin(t_env *env_vars, char *new_var);
int		is_valid_var_name(char *var);
int		check_duplicate(t_env *env_vars, char *new_var);
int		echo_builtin(t_main *main, t_env *env);
int		exit_builtin(t_main *main);
int		exec_builtin(t_env *env_vars, t_main *main);
void	ft_strcpy_memo(char *dst, char *src);

//Environment variables
void	init_env(t_env *env_vars, char **env);
void	check_env(t_env *env_vars);

//echo.c
char	*ft_strremove(char *string, int c);

//exec.c
int		execute_command(t_env *env, t_main *main);
char	*get_env_path(t_env *env);
char	*get_cmd_path(t_main *main, char *cmd_path);
//int	parent_process(t_main *main, t_env *env, int i);
int		parent_process(t_main *main, t_env *env, int i, int pipe_created);

//redirections
int		check_for_redirect_output(t_main *main);
int		check_for_redirect_input(t_main *main);
void	handle_output_redirection(t_main *main, int i);
void	handle_input_redirection(t_main *main, int i);

//exec_utils.c
char	*get_env_path(t_env *env);
char	*get_cmd_path(t_main *main, char *cmd_path);
//void	pipe_redirection(t_main *main, t_env *env_vars, int i);
int		pipe_redirection(t_main *main, int i);
char	**build_exec_args(t_main *main, char **exec_args, int i);

//utils/cleanup.c
void	cleanup_split(char **split);
void	free_main(t_main *main_var);
void	free_args(char **args);
void	free_and_nullify(void **ptr);//ACESSORIA DA FREE_PARSED_STRUCT (NORMINETTE)
void	free_parsed_struct(t_main *parsed_struct, int num_commands);//MUDAR FREE_MAIN E TROCAR?

//utils/cleanup_2.c
void	free_args_2(char ***args);

//parse
t_main	*parse_line(char *line);
t_main	*initialize_main(t_main *main_var, int num_commands);

//parse_utils
//1_args.c
char	**copy_args(char **args);//COPY **ARGS
void	remove_args(char **args, int start_index, int num_args);//SHIFT LEFT **ARGS
void	remove_args_first_last_quotes(char *arg);//REMOVE FIRST AND LAST QUOTES FROM ARGS

//2_input_handling.c
char	*prepare_line(char *line, char ***ph_strings); //MALLOC *prepared, CALL handle_input 
void	handle_input(char *line, char *prepared); //CALL handle_quotes, handle_variables, handle_others 
void	handle_others(char *line, char *prepared, int *i, int *j); //JUST COPY, NO REDIR OR VAR
char	*get_last_exit_status(void);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

//3_redirection_and_variables.c
int		check_redir(char **args, int j); //CHECK IF ARGS[J] IS A REDIRECTION
void	redirection(t_main *parsed_struct, char **args, int i, int j); //PARSE REDIRECTIONS
void	handle_variables(char *line, char *prepared, int *i, int *j); //$ - HANDLE ENV VARIABLES 
void	get_var_name(char *line, int *i, char *var_name); //GET ENV VARIABLE NAME
void	replace_var_value(char *var_name, char *prepared, int *j); //REPLACE ENV VARIABLE VALUE

//4_quotes.c
void	handle_quotes(char *line, int *i, int *in_quotes);
int		in_quotes(char *line);//CHECK IF HAS UNESCAPED QUOTES, OR INSIDE SINGLE OR DOUBLE QUOTES
void	clean_quotes(char **args); //REMOVE QUOTES FROM FIRST AND LAST ARGS
void	erase_quotes(char *command); //REMOVE UNESCAPED QUOTES FROM *command
void	remove_double_quotes(char *str); //REMOVE DOUBLE QUOTES FROM STR

//5_command_processing.c
char	*process_command_string(char *command); //INSERT SPACES IN REDIRS, AND REMOVE UNESCAPED QUOTES IN COMMANDS
void	insert_spaces_in_command(char *command, char *changed, int *i, int *j); //INSERT SPACES IN COMMANDS (REDIRECTIONS)
char	**ft_split_args(const char *s, char c); //SPLIT ARGS BY CHAR C
void	process_string(const char *s, char c, t_process_string_params *params);

// char	*insert_spaces(char *command);
// void	process_command(char *command, char *changed); //CALL insert_spaces_in_command TO ALL COMMANDS

//6_pipe_and_redirection.c
void	create_pipe(t_main *command, int i, int num_commands); //CREATE PIPE
void	handle_redirections(t_main *parsed_struct, char **args, int i); //CHECK AND HANDLE REDIRECTIONS
char	*read_quotes(char *delimiter, char *line); //KEEPS INPUT UNTIL CLOSED QUOTES
char	*read_heredoc(char *delimiter); //KEEPS INPUT UNTIL CLOSED HEREDOC
char	*check_closed_quotes(char *line); //CHECK IF QUOTES ARE CLOSED

//7_string_manipulation.c
int		ft_strcpy(char *dst, const char *src); //COPY SRC TO DST
char	*ft_strncpy(char *dest, char *src, size_t n); //COPY N BYTES FROM SRC TO DST
char	*ft_strcat(char *dest, const char *src); //CONCATENATE SRC TO DEST
char	*ft_strswap(char *str, char *substr, char *replacement); //SWAP SUBSTR BY REPLACEMENT IN STR
char	*ft_strnjoin(char const *s1, char const *s2, size_t n); //JOIN N BYTES OF S2 TO S1

//8_is_and_prints.c
int		is_whitespace(char c); //CHECK IF CHAR IS WHITESPACE
int		is_escaped(char *line, int index); //CHECK IF CHAR IS ESCAPED
int		is_char_in_quotes(char *line, int index); //CHECK IF CHAR IS INSIDE QUOTES
void	print_args(char **args); //PRINT **ARGS
void	print_struct(t_main *main_var, int i); //PRINT STRUCT t_main

// char	*handling(char *command);
// char	*pre_handle_quotes(char *command);
// char	*pre_handle_escaped_quotes(char *command);
// void	copy_increment(char *prepared, const char *line, int *i, int *j);

//9_checkers_and_counters.c
void	check_malloc(void *ptr);
void	check_flags(t_main *command, char **args); //USED IN PARSE_LINE
int		check_delimiter(char *delimiter); //USED IN READ_QUOTES AND READ_HEREDOC
int		count_elements(char **elements); //COUNT ELEMENTS IN **ARRAY
void	print_ph_strings(char ***ph_strings);

//10_placeholder_1.c
char	**extract_strings(const char *line, int *numStrings);
char	*generate_placeholder(int occurrence);
void	replace_with_placeholder(char *line);
int		count_occurrences(const char *str, char c);
char	*ft_strsub(char const *s, unsigned int start, size_t len);

//11_placeholder_2.c
void	placeholder(char *line, char ***ph_strings);
void	replace_single_placeholder(char **command,
			char *placeholder, char *replacement);
void	reverse_placeholders(char **command, char ***ph_strings);
void	reverse_placeholders_in_struct(t_main *command, char ***ph_strings);
// void	replace_placeholders(char **command, char ***ph_strings);

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