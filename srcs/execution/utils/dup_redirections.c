/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 15:58:53 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/20 14:11:48 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds_and_exit(t_shell *shell, int fd_1, int fd_2)
{
	if (fd_1 >= EXISTENT)
		close(fd_1);
	if (fd_2 >= EXISTENT)
		close(fd_2);
	error_quit(shell, SYSCALL_ERROR, NULL);
}

void	dup_output_redirection(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redir.into_stdin == EXISTENT)
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == FAILED)
			close_fds_and_exit(shell, cmd->pipefd[1], -1);
	if (cmd->redir.into_file >= EXISTENT)
	{
		if (dup2(cmd->redir.into_file, STDOUT_FILENO) == FAILED)
			close_fds_and_exit(shell, cmd->pipefd[1], -1);
		close(cmd->redir.into_file);
	}
	close(cmd->pipefd[1]);
}

static void	redir_input(t_shell *shell, t_cmd *cmd, int redir_type)
{
	int	fd;

	fd = -1;
	if (redir_type == FROM_STDIN)
		fd = cmd->previous->pipefd[0];
	else if (redir_type == FROM_HEREDOC)
		fd = cmd->redir.from_heredoc;
	else if (redir_type == FROM_FILE)
		fd = cmd->redir.from_file;
	if (dup2(fd, STDIN_FILENO) == FAILED)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		error_quit(shell, SYSCALL_ERROR, NULL);
	}
	close(fd);
	close(cmd->pipefd[0]);
}

void	dup_input_redirection(t_shell *shell, t_cmd *cmd)
{
	if (cmd->redir.from_heredoc >= EXISTENT)
		return (redir_input(shell, cmd, FROM_HEREDOC));
	else if (cmd->redir.from_file >= EXISTENT)
		return (redir_input(shell, cmd, FROM_FILE));
	if (cmd->previous)
		redir_input(shell, cmd, FROM_STDIN);
}
