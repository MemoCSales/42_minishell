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
	// int	redirect_output;

	// redirect_output = check_for_redirect_output(&main[i]);
	if(main[i].output_file != NULL)
	{
		// printf("Output file: %s\n", main[i].output_file);
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
			// perror("");
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

void	parent_process(t_main *main, t_env *env, int i)
{
	if (i != 0) // If not the 1st cmd, closes the ends of the previous pipe
	{
		close(main[i - 1].fd[0]);
		close(main[i - 1].fd[1]);
	}
	waitpid(main[i].pid, &env->status, 0);
}

void	execute_command(t_env *env, t_main *main)
{
	char    **exec_args;
	char	*path_env;
	char	*path_cmd;
	int     i;

	exec_args = NULL;
	if (buildins(main->cmd) != -1)
		exec_buildin(env, main);
	else
	{
		i = 0;
		// printf("i: %d\n", i);
		while (main[i].cmd != NULL)
		{
			main[i].pid = fork();
			if (main[i].pid < 0)
			{
				perror("Error: Unable to fork\n");
				exit(EXIT_FAILURE);
			}
			if (main[i].pid == 0) //Child process
			{
				pipe_redirection(main, i);
				if (main[i].input_file != NULL)
					handle_input_redirection(main, i);
				if (main[i].output_file != NULL)
					handle_output_redirection(main, i);
				exec_args = build_exec_args(main, exec_args, i);
				path_env = get_env_path(env);					// Prepare the env variables!
				path_cmd = get_cmd_path(&main[i], path_env);	// Find the full path of the command
				// print_exec_args(exec_args);
				if (execve(path_cmd, exec_args, env->env_vars) == -1)
				{
					ft_putstr_fd("zsh: command not found: ", 2);
					ft_putendl_fd(main[i].cmd, 2);
					exit(EXIT_FAILURE);
				}
			}
			else // Parent process
				parent_process(main, env, i);
			i++;
		}
	}
}
