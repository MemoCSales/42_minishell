/* ************************************************************************** */
/*                                                                            */
/*   exec.c                     ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_exec_args(char **exec_args)
{
	int	i;
	// int	j;

	i = 0;
	while (exec_args[i])
	{
		printf("arg[%d]:%s\n", i, exec_args[i]);
		i++;
	}
}

// int	check_for_redirect_output(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while(main->args[i] != NULL)
// 	{
// 		if (ft_strcmp(main->args[i], ">") == 0)
// 			return (1);	// ">" is present in the args
// 		i++;
// 	}
// 	return (0); // ">" Not found
// }

// int	check_for_redirect_input(t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while(main->args[i] != NULL)
// 	{
// 		if (ft_strcmp(main->args[i], "<") == 0)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


void	handle_output_redirection(t_main *main, int i)
{
	int	fd;

	if(main[i].output_file != NULL)
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error: Unable to open file\n");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_input_redirection(t_main *main, int i)
{
	int fd;

	if (main[i].input_file != NULL)
	{
		// printf("Input file: %s --- %d\n", main[i].input_file, i);
		fd = open(main[i].input_file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("zsh: no such file or directory: ", 2);
			ft_putstr_fd(main[i].input_file, 2);
			ft_putstr_fd("\n", 2);
			// close(fd);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

int	parent_process(t_main *main, t_env *env, int i)
{
	if (i != 0) 	// If not the 1st cmd, closes the ends of the previous pipe
	{
		close(main[i - 1].fd[0]);
		close(main[i - 1].fd[1]);
	}
	// close(main[i].fd[0]);
	// close(main[i].fd[1]);
	waitpid(main[i].pid, &env->status, 0);
	return WEXITSTATUS(env->status);
}



int	execute_command(t_env *env, t_main *main)
{
	char    **exec_args;
	char	*path_env;
	char	*path_cmd;
	int     i;
	int		pipe_created;

	pipe_created = 0;
	exec_args = NULL;
	path_cmd = NULL;
	i = 0;
	
	while (main[i].cmd != NULL)
	{
		// printf("COMMAND BEING EXECUTED %s\n", main[i].cmd);
		if (builtins_no_output(main->cmd) != -1)
			return (env->status = exec_builtin(env, &main[i]));
		main[i].pid = fork();
		if (main[i].pid < 0)
		{
			perror("Error: Unable to fork\n");
			exit(EXIT_FAILURE);
		}
		
		if (main[i].pid == 0) //Child process
		{
			// printf("Before the pipe_redirection\n");
			pipe_created = pipe_redirection(main, i);
			// printf("Pipe read end: %d\n", main[i].fd[0]);
			// printf("Pipe write end: %d\n", main[i].fd[1]);
			if (main[i].input_file != NULL)
			{
				// printf("JDFJls -LSAFDSA\n");
				// printf("cmd: main[%s] -index:%d\n",main[i].cmd, i);
				handle_input_redirection(main, i);
			}
			if (main[i].output_file != NULL)
				handle_output_redirection(main, i);
			exec_args = build_exec_args(main, exec_args, i);
			path_env = get_env_path(env);					// Prepare the env variables!
			path_cmd = get_cmd_path(&main[i], path_env);	// Find the full path of the command
			//Grandson - executes
			pid_t	pid;
			// int		status;
			
			pid = fork();
			if (pid == -1)
				printf("Error while forking grandson\n");
			else if (pid == 0)
			{
				if (builtins_with_output(main[i].cmd) != -1)
				{
					// printf("builtin en grandson\n");
					env->status = exec_builtin(env, &main[i]);
					// free(path_cmd);
				}
				else if (execve(path_cmd, exec_args, env->env_vars) == -1)
				{
					ft_putstr_fd("zsh: command not found: ", 2);
					ft_putendl_fd(main[i].cmd, 2);
					env->status = EXEC_ERROR;
					exit(env->status);
				}
			}
			if (pipe_created)
			{
				close(main[i].fd[0]);
				close(main[i].fd[1]);
			}
			// free(exec_args);
			wait(&env->status);
			env->status = WEXITSTATUS(env->status);
			exit(env->status); //check this line
		}
		else // Parent process
		{
			// close(main[i].fd[0]);
			// close(main[i].fd[1]);
			env->status = parent_process(main, env, i);
		}
		i++;
	}
	// free(path_cmd);
	return (env->status);
}
