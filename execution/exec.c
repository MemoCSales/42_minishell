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

// char *find_command_path(char *cmd) {
//     char *path = getenv("PATH");
//     char *path_copy = strdup(path);
//     char *dir = strtok(path_copy, ":");

//     while (dir != NULL) {
//         char *possible_path = malloc(strlen(dir) + strlen(cmd) + 2);
//         strcpy(possible_path, dir);
//         strcat(possible_path, "/");
//         strcat(possible_path, cmd);

//         if (access(possible_path, X_OK) == 0) {
//             free(path_copy);
//             return possible_path;
//         }

//         free(possible_path);
//         dir = strtok(NULL, ":");
//     }

//     free(path_copy);
//     return NULL;
// }


// char	*cmd_path(char *argv, t_env env)
// {
// 	int		i;
// 	char	*prog;
// 	char	*path_cmd;
// 	char	**cmd;

// 	cmd = ft_split(argv, ' ');
// 	i = 0;
// 	while (pipex.dir_paths[i])
// 	{
// 		path_cmd = ft_strjoin(pipex.dir_paths[i], "/");
// 		prog = ft_strjoin(path_cmd, cmd[0]);
// 		free(path_cmd);
// 		if (access(prog, F_OK | X_OK) == 0)
// 		{
// 			cleanup_split(cmd);
// 			return (prog);
// 		}
// 		free(prog);
// 		i++;
// 	}
// 	cleanup_split(pipex.dir_paths);
// 	cleanup_split(cmd);
// 	return (argv);
// }


// void execute_command(t_main *command)
// {
//     pid_t pid = fork(); // Create a new process

//     if (pid < 0) {
//         // Fork failed
//         printf("Error: Unable to fork\n");
//         return;
//     }

//     if (pid == 0) {
//         // Child process
//         // Prepare the arguments for execve
//         int num_args = 0;
//         while (command->args[num_args] != NULL) {
//             num_args++;
//         }

//         // Allocate space for all arguments plus the command name, flags and NULL at the end
//         char **exec_args = malloc((num_args + 3) * sizeof(char *));
//         exec_args[0] = command->cmd;
//         exec_args[1] = command->flags; // Add the flags as the second argument
//         for (int i = 0; i < num_args; i++) {
//             exec_args[i + 2] = command->args[i];
//         }
//         exec_args[num_args + 2] = NULL;

//         // Prepare the environment variables
//         char *envp[] = { getenv("PATH"), NULL };

//         // Find the full path of the command
//         char *full_path = find_command_path(command->cmd);
//         if (full_path == NULL) {
//             printf("Error: Command not found\n");
//             exit(1);
//         }

//         // Execute the command
//         execve(full_path, exec_args, envp);

//         // If execve returns, it means there was an error
//         printf("Error: Failed to execute command\n");
//         exit(1);
//     } else {
//         // Parent process
//         // Wait for the child process to finish
//         waitpid(pid, NULL, 0);
//     }
// }
char	*get_env_path(t_env *env)
{
	int		i;
	char	*path;

	i = 0;
	while (env->env_vars[i] != NULL)
	{
		if (ft_strncmp(env->env_vars[i], "PATH=", 5) == 0)
		{
			path = env->env_vars[i] + 5;
			break;
		}
		i++;
	}
	return (path);
}

char	*get_cmd_path(t_main *main, char *cmd_path)
{
	int	i;
	char	*prog;
	char	*path_cmd;
	char	**dir_paths;

	i = 0;
	dir_paths = ft_split(cmd_path, ':');
	while (dir_paths[i])
	{
		path_cmd = ft_strjoin(dir_paths[i], "/");
		prog = ft_strjoin(path_cmd, main->cmd);
		free(path_cmd);
		if (access(prog, F_OK | X_OK) == 0)
			return (prog);
		free(prog);
		i++;
	}
	cleanup_split(dir_paths);
	return (cmd_path); //check this later
}

void	execute_command(t_env *env, t_main *main)
{
    char    **exec_args;
	char	*path_env;
	char	*path_cmd;
    int     num_args;
    int     i;
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        perror("Error: Unable to fork\n");
    if (pid == 0) //Child process
    {
        num_args = 0;
        while (main->args[num_args] != NULL)
            num_args++;
		printf("%d\n", num_args);
        exec_args = malloc((num_args + 3) * sizeof(char *)); //Allocate memory for args + cmd, flags and NULL
		exec_args[0] = main->cmd;
		exec_args[1] = main->flags;
		i = 0;
		while (i < num_args)
		{
			exec_args[i + 2] = main->args[i];
			i++;
		}
		exec_args[num_args + 2] = NULL;
		// Prepare the env variables!
		// Find the full path of the command
		path_env = get_env_path(env);
		path_cmd = get_cmd_path(main, path_env);

		//Execute the command (you can use the pipex execution part)
		if (execve(path_cmd, exec_args, env->env_vars) == -1)
		{
			ft_putstr_fd("Command not found: ", 2);
			ft_putendl_fd(main->cmd, 2);
			exit(1);
		}
    }
	else //Parent process waits for the child to finish
		waitpid(pid, NULL, 0);
}

// execute that handles redirections
// void execute_command(t_main *main_var)
// {
//     pid_t pid = fork(); // Create a new process

//     if (pid < 0)
//     {
//         // Fork failed
//         perror("minishell");
//     }
//     else if (pid == 0)
//     {
//         // This is the child process
//         if (main_var->flags != NULL && strcmp(main_var->flags, ">") == 0)
//         {
//             // Handle output redirection
//             int fd = open(main_var->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd == -1)
//             {
//                 perror(main_var->args[1]);
//                 exit(EXIT_FAILURE);
//             }
//             dup2(fd, STDOUT_FILENO); // Redirect output to the file
//             close(fd);
//         }
//         if (execvp(main_var->cmd, main_var->args) < 0)
//         {
//             // execvp failed
//             perror(main_var->cmd);
//             exit(EXIT_FAILURE);
//         }
//     }
//     else
//     {
//         // This is the parent process
//         int status;
//         waitpid(pid, &status, 0); // Wait for the child process to finish
//     }
// }
