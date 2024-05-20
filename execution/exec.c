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

	i = 0;
	while (exec_args[i])
	{
		printf("arg[%d]:%s\n", i, exec_args[i]);
		i++;
	}
}

int	handle_heredoc(t_main *main, int i)
{
	char	*tmp;
	int		fd = -1;

	tmp = "/tmp/minishell_heredoc";
	if (main[i].heredoc != NULL)
	{
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
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

	if (main[i].output_file && ft_strcmp(main[i].extra, ">>") == 0)
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (main[i].output_file != NULL)
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

int	parent_process(t_exec_context *context)
{
	if (context->i != 0)
	{
		printf("If i != 0\n");
		if (context->main[context->i - 1].fd[0] != -1)
		{
			printf("Closing read end of current pipe: fd[%d][0]\n", context->i - 1);
			close(context->main[context->i - 1].fd[0]);
		}
		if (context->main[context->i - 1].fd[1] != -1)
		{
			printf("Closing write end of current pipe: fd[%d][1]\n", context->i - 1);
			close(context->main[context->i - 1].fd[1]);
		}
	}
	if (context->pipe_created)
	{
		ft_putstr_fd("If pipe_created\n", 0);
		if (context->main[context->i].fd[0] != -1)
		{
			printf("Closing read end of current pipe: fd[%d][0]\n", context->i);
			close(context->main[context->i].fd[0]);
		}
		if (context->main[context->i].fd[1] != -1)
		{
			printf("Closing write end of current pipe: fd[%d][1]\n", context->i);
			close(context->main[context->i].fd[1]);
		}
	}
	waitpid(context->main[context->i].pid, &context->env->status, 0);
	return WEXITSTATUS(context->env->status);
}


void	handle_child_process(t_exec_context *context)
{
	if (context->main[context->i].output_file != NULL)
		handle_output_redirection(context->main, context->i);
	if (context->main[context->i].heredoc != NULL && ft_strcmp(context->main[context->i].heredoc, ">>") != 0)
	{
		context->heredoc_fd = handle_heredoc(context->main, context->i);
		if (context->heredoc_fd >= 0)
		{
			dup2(context->heredoc_fd, STDIN_FILENO);
			close(context->heredoc_fd);
		}
	}
	if (context->main[context->i].input_file != NULL)
		handle_input_redirection(context->main, context->i);
	context->exec_args = build_exec_args(context->main, context->exec_args, context->i);
	context->path_env = get_env_path(context->env);
	if (context->main[context->i].cmd[0] == '/' || ft_strncmp(context->main[context->i].cmd, "./", 2) == 0)
		context->path_cmd = ft_strdup(context->main[context->i].cmd);
	else
		context->path_cmd = get_cmd_path(&context->main[context->i], context->path_env);
	
	//Debug output
	printf("Executing command: %s\n", context->path_cmd);
    // printf("Pipe created: %d\n", context->pipe_created);
	printf("Pipe write end: %d\n", context->main[context->i].fd[1]);
	printf("Pipe read end: %d\n", context->main[context->i].fd[0]);
    printf("Redirection for command: %s\n", context->main[context->i].cmd);

	context->pipe_created = pipe_redirection(context->main, context->i, context);
	handle_grandson_process(context);
}

void	handle_grandson_process(t_exec_context *context)
{
	context->main[context->i].grandson_pid = fork();
	if (context->main[context->i].grandson_pid == -1)
		error_messages("ERROR_FORK");
	else if (context->main[context->i].grandson_pid == 0)
	{
		if (builtins_with_output(context->main[context->i].cmd) != -1)
		{
			free(context->path_cmd);
			context->env->status = exec_builtin(context->env, &context->main[context->i]);
		}
		else 
		{
			printf("Executing execve for command: %s\n", context->path_cmd);
			if (execve(context->path_cmd, context->exec_args, context->env->env_vars) == -1)
			{
				ft_putstr_fd(context->main[context->i].cmd, 2);
				ft_putstr_fd(": command not found\n", 2);
				context->env->status = EXEC_ERROR;
				exit(context->env->status);
			}
		}
	}
	if (context->heredoc_fd != -1)
		close(context->heredoc_fd);
	waitpid(context->main[context->i].grandson_pid, &context->env->status, 0);
	cleanup_split(context->exec_args);
	context->env->status = WEXITSTATUS(context->env->status);
	exit(context->env->status);
}

int	execute_with_commands(t_exec_context *context)
{
	if (context->main[context->i].cmd != NULL && ft_strlen(context->main[context->i].cmd) > 0)
	{
		while (context->main[context->i].cmd != NULL)
		{
			if (builtins_no_output(context->main->cmd) != -1)
				return (context->env->status = exec_builtin(context->env, &context->main[context->i]));
			context->main[context->i].pid = fork();
			if (context->main[context->i].pid < 0)
				error_messages("ERROR_FORK");
			if (context->main[context->i].pid == 0)
				handle_child_process(context);
			else
				context->env->status = parent_process(context);
			context->i++;
		}
		return (context->env->status);
	}
	return (-1);
}

int execute_without_commands(t_exec_context *context)
{
	if (context->main[context->i].cmd == NULL && (context->main[context->i].input_file || context->main[context->i].output_file || context->main[context->i].heredoc))
	{
		context->env->status = exec_without_cmds(context);
		return (context->env ->status);
	}
	else
	{
		context->env->status = 0;
		return (context->env->status);
	}
}

int	execute_command(t_env *env, t_main *main)
{
	t_exec_context	context;
	int				status;

	context.main = main;
	context.env = env;
	initialize_context(&context);

	status = execute_with_commands(&context);
	if (status != -1)
		return (status);
	return (execute_without_commands(&context));
}

void	initialize_context(t_exec_context *context)
{
	context->i = 0;
	context->exec_args = NULL;
	context->path_cmd = NULL;
	context->heredoc_fd = -1;
	context->pipe_created = 0;
}

int	exec_without_cmds(t_exec_context *context)
{
	if (context->main[context->i].heredoc != NULL)
	{
		context->heredoc_fd = handle_heredoc(context->main, context->i);
	}
	if ((context->main[context->i].input_file != NULL && context->main[context->i].output_file != NULL) || (context->main[context->i].heredoc != NULL && context->main[context->i].output_file))
	{
		printf("HANDLE FILE REDIRECTION\n");
		handle_file_redirection(context->main, context->i, context->heredoc_fd);
	}
	if (context->heredoc_fd)
		close(context->heredoc_fd);
	return (context->env->status);
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


// int	pipe_redirection(t_main *main, int i)
// {
// 	if (i != 0) // If not the first cmd, redirect input from the previous pipe
// 	{
// 		if (main[i - 1].fd[1] != -1)
// 			close(main[i - 1].fd[1]);
// 		if (dup2(main[i - 1].fd[0], STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (main[i - 1].fd[0] != -1)
// 			close(main[i - 1].fd[0]);
// 	}
// 	if (main[i + 1].cmd != NULL) // If not the last cmd (first command counts), redirect output to the next pipe
// 	{
// 		if (main[i].fd[0] != -1)
// 			close(main[i].fd[0]);
// 		if (dup2(main[i].fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (main[i].fd[1] != -1)
// 			close(main[i].fd[1]);
// 		return (1);
// 	}
// 	return (0);
// }
// int	parent_process(t_main *main, t_env *env, int i, int pipe_created)
// {
// 	if (pipe_created)
// 	{
// 		close(main[i].fd[0]);
// 		close(main[i].fd[1]);
// 	}
// 	if (i != 0) //If not the 1st cmd, closes the ends of the previous pipe
// 	{
// 		close (main[i - 1].fd[0]);
// 		close (main[i - 1].fd[1]);
// 	}
// 	waitpid(main[i].pid, &env->status, 0);
// 	return WEXITSTATUS(env->status);
// }

// int	execute_command(t_env *env, t_main *main)
// {
// 	char	**exec_args;
// 	char	*path_env;
// 	char	*path_cmd;
// 	int		i;
// 	int		pipe_created;
// 	int		heredoc_fd;
// 	// pid_t	pid;

// 	pipe_created = 0;
// 	heredoc_fd = 0;
// 	exec_args = NULL;
// 	path_cmd = NULL;
// 	i = 0;
// 	if (main[i].cmd != NULL && ft_strlen(main[i].cmd) > 0)
// 	{
// 		while (main[i].cmd != NULL)
// 		{
// 			if (builtins_no_output(main->cmd) != -1)
// 				return (env->status = exec_builtin(env, &main[i]));
// 			main[i].pid = fork();
// 			if (main[i].pid < 0)
// 				error_messages("ERROR_FORK");
// 			if (main[i].pid == 0) //Child process
// 			{
// 				if (main[i].output_file != NULL)
// 				{
// 					handle_output_redirection(main, i);
// 				}
// 				if (main[i].heredoc != NULL && ft_strcmp(main[i].heredoc, ">>") != 0)
// 				{
// 					// printf("HEREDOC EXEC\n");
// 					heredoc_fd = handle_heredoc(main, i);
// 					if (heredoc_fd >= 0)
// 					{
// 						dup2(heredoc_fd, STDIN_FILENO);
// 						close(heredoc_fd);
// 					}
// 				}
// 				if (main[i].input_file != NULL)
// 				{
// 					// printf("INPUT REDIRECTION\n");
// 					handle_input_redirection(main, i);
// 				}
// 				exec_args = build_exec_args(main, exec_args, i);
// 				path_env = get_env_path(env); // Prepare the env variables!
// 				if (main[i].cmd[0] == '/' || ft_strncmp(main[i].cmd, "./", 2) == 0)
// 					path_cmd = ft_strdup(main[i].cmd);
// 				else
// 					path_cmd = get_cmd_path(&main[i], path_env); // Find full path of command
// 				//Grandson - executes
// 				pipe_created = pipe_redirection(main, i);

// 				main[i].grandson_pid = fork();
// 				if (main[i].grandson_pid  == -1)
// 					printf("Error while forking grandson\n");
// 				else if (main[i].grandson_pid  == 0)
// 				{
// 					if (builtins_with_output(main[i].cmd) != -1)
// 					{
// 						free(path_cmd);
// 						env->status = exec_builtin(env, &main[i]);
// 					}
// 					else if (execve(path_cmd, exec_args, env->env_vars) == -1)
// 					{
// 						ft_putstr_fd(main[i].cmd, 2);
// 						ft_putstr_fd(": command not found\n", 2);
// 						env->status = EXEC_ERROR;
// 						exit(env->status);
// 					}
// 				}
// 					close(heredoc_fd);
// 					// wait(&env->status);
// 					waitpid(main[i].grandson_pid, &env->status, 0);
// 					cleanup_split(exec_args);
// 					env->status = WEXITSTATUS(env->status);
// 					exit (env->status); //check this line
// 					//grandson finished
// 				// }
// 			}
// 			else // Parent process
// 			{
// 				env->status = parent_process(main, env, i, pipe_created);
// 			}
// 			i++;
// 			// free(path_cmd);
// 		}
// 		return (env->status);
// 	}
// 	else if (main[i].cmd == NULL && (main[i].input_file || main[i].output_file || main[i].heredoc))
// 	{
// 		env->status = exec_without_cmds(main, env, i);
// 		return (env->status);
// 	}
// 	else
// 	{
// 		env->status = 0;
// 		return (env->status);
// 	}
// }

//Check if I need to add a status variable and change its value
// int	exec_without_cmds(t_main *main, t_env *env, int i)
// {
// 	int	heredoc_fd;

// 	heredoc_fd = 0;
// 	printf("EXECUTION WITH NO ARGUMENTS\n");
// 	if (main[i].heredoc != NULL)
// 	{
// 		heredoc_fd = handle_heredoc(main, i);
// 	}
// 	printf("INPUT_FILE: %s\n", main[i].input_file);
// 	printf("OUTPUT FILE: %s\n", main[i].output_file);
// 	if ((main[i].input_file != NULL && main[i].output_file != NULL) || (main[i].heredoc != NULL && main[i].output_file))
// 	{
// 		printf("HANDLE FILE REDIRECTION\n");
// 		handle_file_redirection(main, i, heredoc_fd);
// 	}
// 	if (heredoc_fd)
// 		close(heredoc_fd);
// 	return (env->status);
// }


// int	execute_command2(t_env *env, t_main *main)
// {
// 	char	**exec_args;
// 	char	*path_env;
// 	char	*path_cmd;
// 	int		i;
// 	int		pipe_created;
// 	int		heredoc_fd;

// 	pipe_created = 0;
// 	heredoc_fd = 0;
// 	exec_args = NULL;
// 	path_cmd = NULL;
// 	i = 0;
// 	if (main[i].cmd != NULL && ft_strlen(main[i].cmd) > 0)
// 	{
// 		while (main[i].cmd != NULL)
// 		{
// 			printf("COMMAND BEING EXECUTED %s -- %d\n", main[i].cmd, i);
// 			// printf("INPUT FILE %s\n", main[i].input_file);
// 			// printf("OUTPUT FILE %s\n", main[i].output_file);
// 			if (builtins_no_output(main->cmd) != -1)
// 				return (env->status = exec_builtin(env, &main[i]));
// 			if (main[i + 1].cmd != NULL) {
// 				// printf("Setting up pipe between command %d (%s) and command %d (%s)\n", i, main[i].cmd, i + 1, main[i + 1].cmd);
// 			}
// 			main[i].pid = fork();
// 			if (main[i].pid < 0)
// 				error_messages("ERROR_FORK");
// 			if (main[i].pid == 0) //Child process
// 			{
// 				// printf("Child: Im the child process with PID: %d\n", main[i].pid);
// 				pipe_created = pipe_redirection(main, i);
// 				if (main[i].output_file != NULL)
// 				{
// 					// printf("OUTPUT REDIRECTION\n");
// 					handle_output_redirection(main, i);
// 				}
// 				if (main[i].heredoc != NULL && ft_strcmp(main[i].heredoc, ">>") != 0)
// 				{
// 					// printf("HEREDOC EXEC\n");
// 					// handle_heredoc(main, i);
// 					heredoc_fd = handle_heredoc(main, i);
// 					// printf("HEREDOC_DOC: %d\n", heredoc_fd);
// 					if (heredoc_fd >= 0)
// 					{
// 						// printf("HEREDOC_FD: %d\n", heredoc_fd);
// 						dup2(heredoc_fd, STDIN_FILENO);
// 						close(heredoc_fd);
// 					}
// 				}
// 				if (main[i].input_file != NULL)
// 				{
// 					// printf("INPUT REDIRECTION\n");
// 					handle_input_redirection(main, i);
// 				}
// 				exec_args = build_exec_args(main, exec_args, i);
// 				path_env = get_env_path(env); // Prepare the env variables!
// 				if (main[i].cmd[0] == '/' || ft_strncmp(main[i].cmd, "./", 2) == 0)
// 					path_cmd = ft_strdup(main[i].cmd);
// 				else
// 					path_cmd = get_cmd_path(&main[i], path_env); // Find full path of command
// 				if (builtins_with_output(main[i].cmd) != -1)
// 				{
// 					free(path_cmd);
// 					env->status = exec_builtin(env, &main[i]);
// 				}
// 				else if (execve(path_cmd, exec_args, env->env_vars) == -1)
// 				{
// 					{
// 						ft_putstr_fd(main[i].cmd, 2);
// 						ft_putstr_fd(": command not found\n", 2);
// 						env->status = EXEC_ERROR;
// 						exit(env->status);
// 					}
// 				}
// 			}
			
// 			else // Parent process
// 			{
// 				// if (pipe_created)
// 				// {
// 				// 	close(main[i].fd[0]);
// 				// 	close(main[i].fd[1]);
// 				// }
// 				// if (i != 0) //If not the 1st cmd, closes the ends of the previous pipe
// 				// {
// 				// 	close (main[i - 1].fd[0]);
// 				// 	close (main[i - 1].fd[1]);
// 				// }
// 				// printf("Parent: Im the parent process with PID: %d\n", main[i].pid);
// 				env->status = parent_process(main, env, i, pipe_created);
// 			}
// 			// printf("Adding one to the counter\n");
// 			// i++;
// 			// free(path_cmd);
// 		}
// 		// while ((main[i].pid = waitpid(-1, &env->status, 0)) > 0);
// 		return (env->status);
// 	}
// 	else if (main[i].cmd == NULL && (main[i].input_file || main[i].output_file || main[i].heredoc))
// 	{
// 		env->status = exec_without_cmds(main, env, i);
// 		return (env->status);
// 	}
// 	else
// 	{
// 		env->status = 0;
// 		return (env->status);
// 	}
// }