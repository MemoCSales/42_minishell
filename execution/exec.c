/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcruz-sa <mcruz-sa@student.42.fr>          +#+  +:+       +#+        */
/*   By: demrodri <demrodri@student.42wolfsburg.de>*/
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:55:37 by mcruz-sa          #+#    #+#             */
/*   Updated: 2024/03/29 13:56:13 by mcruz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	pipe_redirection(t_main *main, int i)
// {
// 	if (i != 0) // If not the first cmd, redirect input from the previous pipe
// 	{
// 		// printf("%s\n", main[i].cmd);
// 		// printf("%d\n", main[i].fd[0]);
// 		if (dup2(main[i - 1].fd[0], STDIN_FILENO) == -1) 
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		// close(main[i - 1].fd[0]);
// 		close(main[i - 1].fd[1]);
// 	}
// 	if (main[i + 1].cmd != NULL) // If not the last cmd, redirect output to the next pipe
// 	{
// 		// printf("%s\n", main[i].cmd);
// 		// printf("%d\n", main[i].fd[1]);
// 		if (dup2(main[i].fd[1], STDOUT_FILENO) == -1) 
// 		{
// 			perror("dup2 error");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(main[i].fd[0]);
// 		// close(main[i].fd[1]);
// 	}
// }

// int	builtins_no_output(char *cmd)
// {
// 	if (ft_strcmp(cmd, "cd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "unset") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "export") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "exit") == 0)
// 		return(1);
// 	return (-1);
// }

// int	builtins_with_output(char *cmd)
// {
// 	if (ft_strcmp(cmd, "pwd") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "env") == 0)
// 		return (1);
// 	else if (ft_strcmp(cmd, "echo") == 0)
// 		return (1);
// 	return (-1);
// }

// int	exec_builtin(t_env *env_vars, t_main *main)
// {
// 	if (ft_strcmp(main->cmd, "cd") == 0)
// 		return (env_vars->status = cd_builtin(main->args[0]));
// 	else if (ft_strcmp(main->cmd, "pwd") == 0)
// 		return (env_vars->status = pwd_builtin());
// 	else if (ft_strcmp(main->cmd, "env") == 0)
// 		return (env_vars->status = env_builtin(env_vars));
// 	else if (ft_strcmp(main->cmd, "unset") == 0)
// 		return (env_vars->status = unset_builtin(env_vars, main->args[0]));
// 	else if (ft_strcmp(main->cmd, "export") == 0)
// 		return (env_vars->status = export_builtin(env_vars, main->args[0]));
// 	else if (ft_strcmp(main->cmd, "echo") == 0)
// 		return (env_vars->status = echo_builtin(main, env_vars));
// 	else if (ft_strcmp(main->cmd, "exit") == 0)
// 	{
// 		return (env_vars->status = exit_builtin(main));
// 		exit(env_vars->status);
// 	}
// 	return (-1);
// }




/*----------------------------------------------------------------------------------*/


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
		// printf("Input file: %s\n", main[i].input_file);
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

	exec_args = NULL;
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
			pipe_redirection(main, i);
			// printf("Pipe read end: %d\n", main[i].fd[0]);
			// printf("Pipe write end: %d\n", main[i].fd[1]);
			if (main[i].input_file != NULL)
				handle_input_redirection(main, i);
			if (main[i].output_file != NULL)
				handle_output_redirection(main, i);
			exec_args = build_exec_args(main, exec_args, i);
			path_env = get_env_path(env);					// Prepare the env variables!
			path_cmd = get_cmd_path(&main[i], path_env);	// Find the full path of the command

			//Grandson - executes
			pid_t	pid;
			int		status;
			
			pid = fork();
			if (pid == -1)
				printf("Error while forking grandson\n");
			else if (pid == 0)
			{
				if (builtins_with_output(main[i].cmd) != -1)
				{
					// printf("builtin en grandson\n");
					env->status = exec_builtin(env, &main[i]);
				}
				else if (execve(path_cmd, exec_args, env->env_vars) == -1)
				{
					ft_putstr_fd("zsh: command not found: ", 2);
					ft_putendl_fd(main[i].cmd, 2);
					return (EXEC_ERROR);
				}
			}
			close(main[i].fd[0]);
			close(main[i].fd[1]);
			wait(&status);
			// printf("before exit process\n");
			exit(EXIT_SUCCESS); //check this line
		}
		else // Parent process
		{
			// close(main[i].fd[0]);
			// close(main[i].fd[1]);
			env->status = parent_process(main, env, i);
		}
		i++;
	}
	
	return (env->status);
}
