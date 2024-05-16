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

int	handle_heredoc(t_main *main, int i)
{
	char	*tmp;
	int		fd = -1;

	// printf("INSIDE HANDLE HEREDOC\n");
	tmp = "/tmp/minishell_heredoc";
	if (main[i].heredoc != NULL)
	{
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		// printf("INISDIE HEREDOC\n");
		write(fd, main[i].heredoc, ft_strlen(main[i].heredoc));
		close(fd);
		fd = open(tmp, O_RDONLY);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
	}
	return (fd);
}

void	handle_output_redirection(t_main *main, int i)
{
	int	fd;

	if (main[i].output_file && ft_strcmp(main[i].extra, ">>") == 0) //appending
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (main[i].output_file != NULL) //overwritting an existing file or creating a newone
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
}

void	handle_input_redirection(t_main *main, int i)
{
	int	fd;

	if (main[i].input_file != NULL)
	{
		// printf("Input file: %s --- %d\n", main[i].input_file, i);
		fd = open(main[i].input_file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd ("zsh: No such file or directory: ", 2);
			ft_putstr_fd (main[i].input_file, 2);
			ft_putstr_fd ("\n", 2);
			exit (EXIT_FAILURE);
		}
		dup2 (fd, STDIN_FILENO);
		close (fd);
	}
}

int	parent_process(t_main *main, t_env *env, int i, int pipe_created)
{
	if (i != 0) //If not the 1st cmd, closes the ends of the previous pipe
	{
		close (main[i - 1].fd[0]);
		close (main[i - 1].fd[1]);
	}
	waitpid(main[i].pid, &env->status, 0);
	if (pipe_created)
	{
		close(main[i].fd[0]);
		close(main[i].fd[1]);
	}
	// printf("PARENT EXIT CODE: %d\n", env->status);
	return WEXITSTATUS(env->status);
}

int	execute_command(t_env *env, t_main *main)
{
	char	**exec_args;
	char	*path_env;
	char	*path_cmd;
	int		i;
	int		pipe_created;
	int		heredoc_fd;
	pid_t	pid;

	pipe_created = 0;
	heredoc_fd = 0;
	exec_args = NULL;
	path_cmd = NULL;
	i = 0;
	if (main[i].cmd != NULL && ft_strlen(main[i].cmd) > 0)
	{
		while (main[i].cmd != NULL)
		{
			// printf("COMMAND BEING EXECUTED %s -- %d\n", main[i].cmd, i);
			// printf("INPUT FILE %s\n", main[i].input_file);
			// printf("OUTPUT FILE %s\n", main[i].output_file);
			if (builtins_no_output(main->cmd) != -1)
				return (env->status = exec_builtin(env, &main[i]));
			main[i].pid = fork();
			if (main[i].pid < 0)
				error_messages("ERROR_FORK");
			if (main[i].pid == 0) //Child process
			{
				pipe_created = pipe_redirection(main, i);
				// printf("PIPES EXITS: %d\n", pipe_created);
				// if (pipe_created)
				// {
				// 	// printf("CLOSING PIPES IN SON PROCESS\n");
				// 	close(main[i].fd[1]);
				// 	dup2(main[i].fd[0], STDIN_FILENO);
				// }
				// printf("PIPE REDIRECTION: %d\n", pipe_created);
				// printf("Pipe read end: %d\n", main[i].fd[0]);
				// printf("Pipe write end: %d\n", main[i].fd[1]);
				// printf("Outfile: %s\n", main[i].output_file);
				if (main[i].output_file != NULL)
				{
					// printf("OUTPUT REDIRECTION\n");
					handle_output_redirection(main, i);
				}
				if (main[i].heredoc != NULL && ft_strcmp(main[i].heredoc, ">>") != 0)
				{
					// printf("HEREDOC EXEC\n");
					// handle_heredoc(main, i);
					heredoc_fd = handle_heredoc(main, i);
					// printf("HEREDOC_DOC: %d\n", heredoc_fd);
					if (heredoc_fd >= 0)
					{
						// printf("HEREDOC_FD: %d\n", heredoc_fd);
						dup2(heredoc_fd, STDIN_FILENO);
						close(heredoc_fd);
					}
				}
				if (main[i].input_file != NULL)
				{
					// printf("INPUT REDIRECTION\n");
					handle_input_redirection(main, i);
				}
				exec_args = build_exec_args(main, exec_args, i);
				path_env = get_env_path(env); // Prepare the env variables!
				if (main[i].cmd[0] == '/' || ft_strncmp(main[i].cmd, "./", 2) == 0)
					path_cmd = ft_strdup(main[i].cmd);
				else
					path_cmd = get_cmd_path(&main[i], path_env);
											// Find full path of command
				//Grandson - executes
				pid = fork();
				if (pid == -1)
					printf("Error while forking grandson\n");
				else if (pid == 0)
				{
					if (pipe_created)
					{
						close(main[i].fd[0]);
						dup2(main[i].fd[1],STDOUT_FILENO);
					}
					if (builtins_with_output(main[i].cmd) != -1)
					{
						free(path_cmd);
						env->status = exec_builtin(env, &main[i]);
					}
					else if (execve(path_cmd, exec_args, env->env_vars) == -1)
					{
						ft_putstr_fd(main[i].cmd, 2);
						ft_putstr_fd(": command not found\n", 2);
						env->status = EXEC_ERROR;
						exit(env->status);
					}
				}
				if (pipe_created)
				{
					close (main[i].fd[0]);
					close (main[i].fd[1]);
				}
				close(heredoc_fd);
				wait(&env->status);
				cleanup_split(exec_args);
				// free(path_cmd);
				env->status = WEXITSTATUS(env->status);
				exit (env->status); //check this line
				//grandson finished
			}
			else // Parent process
			{
				env->status = parent_process(main, env, i, pipe_created);
			}
			i++;
			// free(path_cmd);
		}
		return (env->status);
	}
	else if (main[i].cmd == NULL && (main[i].input_file || main[i].output_file || main[i].heredoc))
	{
		env->status = exec_without_cmds(main, env, i);
		return (env->status);
	}
	else
	{
		env->status = 0;
		return (env->status);
	}
}

//Check if I need to add a status variable and change its value
int	exec_without_cmds(t_main *main, t_env *env, int i)
{
	int	heredoc_fd;

	heredoc_fd = 0;
	printf("EXECUTION WITH NO ARGUMENTS\n");
	// pipe_created = pipe_redirection(main, i);
	// printf("PIPE REDIRECTION: %d\n", pipe_created);
	if (main[i].heredoc != NULL)
	{
		// printf("HEREDOC EXEC\n");
		heredoc_fd = handle_heredoc(main, i);
	}
	printf("INPUT_FILE: %s\n", main[i].input_file);
	printf("OUTPUT FILE: %s\n", main[i].output_file);
	if ((main[i].input_file != NULL && main[i].output_file != NULL) || (main[i].heredoc != NULL && main[i].output_file))
	{
		printf("HANDLE FILE REDIRECTION\n");
		handle_file_redirection(main, i, heredoc_fd);
	}
	if (heredoc_fd)
		close(heredoc_fd);
	return (env->status);
}


void	handle_file_redirection(t_main *main, int i, int heredoc_fd)
{
	char	*tmp;
	int		in;
	int		out;

	in = 0;
	if (main[i].input_file)
	{
		in = open(main[i].input_file, O_RDONLY);
		if (in < 0)
			error_messages("ERROR_OPEN_FILE");
	}
	else if (heredoc_fd)
	{
		tmp = "/tmp/minishell_heredoc";
		in = open(tmp, O_RDONLY);
		if (in < 0)
			error_messages("ERROR_OPEN_FILE");
	}
	out = open(main[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out < 0)
		error_messages("ERROR_OPEN_FILE");
	close(in);
	close(out);
}
