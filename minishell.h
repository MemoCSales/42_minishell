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
# include <assert.h> // to test parsing functions
# include <stdio.h> // to test parsing functions

# define MAX_CMD_LEN 1024

typedef struct s_main
{
	char	*cmd;
	char	*flags;
	char	**args;
	char	*input_file;
	char	*output_file;
	char	*heredoc;
	int		fd[2];
	pid_t	pid;
}			t_main;

typedef struct s_env
{
	char	**env_vars;
	int		status;
}			t_env;

// main
void	main_loop(t_env env_var, t_main *main_var);

// Functions for the buildins
int			buildins(char *cmd);
void		cd_buildin(char *path);
void		pwd_buildin(void);
void		env_buildin(t_env *env_vars);
void		unset_buildin(t_env *env_vars, char *var_name);
int			find_index(t_env *env_vars, char *var_name);
void		export_buildin(t_env *env_vars, char *new_var);
int			check_duplicate(t_env *env_vars, char *new_var);
void		echo_buildin(t_main *main);
void		exec_buildin(t_env *env_vars, t_main *main);

// Environment variables
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);

// exec.c
void		execute_command(t_env *env, t_main *main);
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);

// parsing
t_main		*parse_line(char *line);
int			count_cmds(char **cmds);
char		**copy_args(char **args);

// utils
void		cleanup_split(char **split);
void		free_main(t_main *main_var);
void		print_struct(t_main *main_var, int num_commands);
void		free_args(char **args); //added due to segfault while testing parsing

// parse_utils
t_main		*initialize_main(t_main *main_var);
int 		ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dest, char *src, size_t n);
void 		test_parser();

#endif