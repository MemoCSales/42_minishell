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

# define MAX_CMD_LEN 1024

typedef struct s_main
{
	char	*cmd;
	char	*flags;
	char	**args;
	int		fd[2];
	pid_t	pid;
}			t_main;

typedef struct s_env
{
	char	**env_vars;
	int		status;
}			t_env;

// Functions for the buildins
int			buildins(char *cmd);
void		cd_buildin(char *path);
void		pwd_buildin(void);
void		env_buildin(t_env *env_vars);
void		unset_buildin(t_env *env_vars, char *var_name);
int			find_index(t_env *env_vars, char *var_name);
void		export_buildin(t_env *env_vars, char *new_var);
int			check_duplicate(t_env *env_vars, char *new_var);
void		echo_buildin(char **cmd);
void		exec_buildin(t_env *env_vars, t_main *main);

// Environment variables
void		init_env(t_env *env_vars, char **env);
void		check_env(t_env *env_vars);

// exec.c
void		execute_command(t_env *env, t_main *main);
char		*get_env_path(t_env *env);
char		*get_cmd_path(t_main *main, char *cmd_path);
void	execute_piped_commands(t_main *main, t_env *env, int num_cmd);
// cleanup.c
void		cleanup_split(char **split);

#endif