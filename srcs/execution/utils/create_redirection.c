/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:54:41 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/20 17:44:58 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_file(t_cmd *cmd, char *file_name, int redir_type)
{
	if (redir_type == APPEND)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redir_type == TRUNC)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->redir.into_file == FAILED)
	{
		close(cmd->redir.into_file);
		if (errno == EBADF)
			errno = ENOENT;
		return (errno);
	}
	return (IS_VALID);
}

static int	check_for_existing_file(t_cmd *cmd, char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd > 0)
	{
		cmd->redir.from_file = fd;
		return (IS_VALID);
	}
	return (errno);
}

static char *search_for_file_name(t_token *token)
{
	while (token)
	{
		if (token->redir == IS_FILE)
			return (token->word);
		token = token->next;
	}
	return (NULL);
}

void	create_redirection(t_shell *shell, t_cmd *cmd, t_token *token)
{
	char	*file_name;
	int		redir_status;

	redir_status = IS_VALID;
	while (token)
	{
		file_name = search_for_file_name(token);
		if (token->redir == INPUT_REDIR)
			redir_status = check_for_existing_file(cmd, file_name);
		else if (token->redir == APPEND || token->redir == TRUNC)
			redir_status = create_file(cmd, file_name, token->redir);
		if (redir_status >= IS_NOT_VALID)
			error_quit(shell, SYSCALL_ERROR, file_name);
		if (token->redir == PIPE)
			cmd->redir.into_stdin = EXISTENT;
		token = token->next;
	}
}
