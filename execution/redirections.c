/* ************************************************************************** */
/*                                                                            */
/*   redirections.c             ψΨ MiniℍΞLL Ψψ            :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*   By: mcruz-sa <mcruz-sa@student.42.de>            +:+ +:+         +:+     */
/*   By: demrodri <demrodri@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:46:39 by both              #+#    #+#             */
/*   Updated: 2023/12/17 19:47:12 by both             ###   ########.de       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_input_redirection(t_main *main, int i)
{
	int	fd;

	fd = -1;
	if (main[i].input_file != NULL)
	{
		fd = open(main[i].input_file, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("MiniℍΞLL: No such file or directory: ", 2);
			ft_putstr_fd(main[i].input_file, 2);
			ft_putstr_fd("\n", 2);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		if (fd != -1)
			close(fd);
	}
}

void	handle_output_redirection(t_main *main, int i)
{
	int	fd;

	fd = -1;
	if (main[i].output_file && ft_strcmp(main[i].extra, ">>") == 0)
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
	}
	else if (main[i].output_file != NULL)
	{
		fd = open(main[i].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		dup2(fd, STDOUT_FILENO);
		if (fd != -1)
			close(fd);
	}
}

int	handle_heredoc(t_main *main, int i)
{
	char	*tmp;
	int		fd;

	fd = -1;
	tmp = "/tmp/minishell_heredoc";
	if (main[i].heredoc != NULL)
	{
		fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
		write(fd, main[i].heredoc, ft_strlen(main[i].heredoc));
		if (fd != -1)
			close(fd);
		fd = open(tmp, O_RDONLY);
		if (fd < 0)
			error_messages("ERROR_OPEN_FILE");
	}
	return (fd);
}

void	handle_file_redirection(t_main *main, int i, int heredoc_fd)
{
	char	*tmp;
	int		in;
	int		out;

	in = -1;
	out = -1;
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

void	exec_handle_redirections(t_exec_context *context)
{
	if (context->main[context->i].output_file != NULL)
		handle_output_redirection(context->main, context->i);
	if (context->main[context->i].heredoc != NULL
		&& ft_strcmp(context->main[context->i].heredoc, ">>") != 0)
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
}
