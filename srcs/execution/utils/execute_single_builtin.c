/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:14:39 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/16 14:56:27 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_and_exit(t_shell *shell, t_cmd *cmd, char **argv)
{
	cmd->ft_builtin(shell, argv);
	ft_exit(shell, argv);
}

int	execute_single_builtin_cmd(t_shell *shell, t_cmd *cmd, char **argv)
{
	create_redirection(shell, cmd, cmd->token_list, SINGLE_BUILTIN);
	if (cmd->ft_builtin == NULL) // si single builtin et redir failed
		return (exit_status);
	if (cmd->redir.from_file >= EXISTENT)
		close(cmd->redir.from_file);
	else if (cmd->redir.from_heredoc >= EXISTENT)
		close(cmd->redir.from_heredoc);
	if (cmd->redir.into_file >= EXISTENT)
	{
		// free (*argv);
		// (*argv) = NULL;
		(*argv) = ft_itoa(cmd->redir.into_file);
	}
	return (cmd->ft_builtin(shell, argv));
}
