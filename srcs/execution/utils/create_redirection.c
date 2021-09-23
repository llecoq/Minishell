/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:54:41 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/23 15:42:40 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_file(t_cmd *cmd, char *file_name, int redir_type)
{
	if (cmd->redir.into_file >= EXISTENT)
		close(cmd->redir.into_file);
	if (redir_type == APPEND)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redir_type == TRUNC)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->redir.into_file == FAILED)
	{
		if (errno == EBADF)
			errno = ENOENT;
		return (errno);
	}
	free_set_null((void **)&cmd->redir.file_name);
	return (IS_VALID);
}

static int	check_for_existing_file(t_cmd *cmd, char *file_name)
{
	int		fd;

	if (cmd->redir.from_file >= EXISTENT)
		close(cmd->redir.from_file);
	fd = open(file_name, O_RDONLY);
	if (fd > 0)
	{
		free_set_null((void **)&cmd->redir.file_name);
		cmd->redir.from_file = fd;
		return (IS_VALID);
	}
	return (errno);
}

void	redir_error(t_shell *shell, t_cmd *cmd, int redir_status, int process)
{
	if (cmd->redir.into_file >= EXISTENT)
		close(cmd->redir.into_file);
	if (cmd->redir.from_file >= EXISTENT)
		close(cmd->redir.into_file);
	if (cmd->redir.from_heredoc >= EXISTENT)
		close(cmd->redir.from_heredoc);
	if (redir_status != AMBIGUOUS_REDIRECT)
		redir_status = SYSCALL_ERROR;
	if (process == SINGLE_BUILTIN)
	{
		ft_printf(STDERR_FILENO, "minishell: %s: ", cmd->redir.file_name);
		free_set_null((void **)&cmd->redir.file_name);
		error(shell, redir_status, cmd->redir.file_name);
		cmd->ft_builtin = NULL;
		return ;
	}
	error_quit(shell, redir_status, cmd->redir.file_name);
}

void	create_redirection(t_shell *shell, t_cmd *cmd, t_token *tk, int process)
{
	char	*file_name;
	int		redir_status;

	redir_status = IS_VALID;
	while (tk)
	{
		file_name = search_and_expand_file_name(shell, cmd, tk);
		if (ambiguous_redirect(cmd, file_name))
			return (redir_error(shell, cmd, AMBIGUOUS_REDIRECT, process));
		if (tk->redir == INPUT_REDIR)
			redir_status = check_for_existing_file(cmd, file_name);
		else if (tk->redir == APPEND || tk->redir == TRUNC)
			redir_status = create_file(cmd, file_name, tk->redir);
		if (redir_status >= IS_NOT_VALID)
			return (redir_error(shell, cmd, redir_status, process));
		if (tk->redir == PIPE)
			cmd->redir.into_stdin = EXISTENT;
		tk = tk->next;
	}
}
