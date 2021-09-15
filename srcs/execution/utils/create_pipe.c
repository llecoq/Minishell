/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:48:52 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/15 10:37:27 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_shell *shell, t_cmd *cmd)
{
	if (pipe(cmd->pipefd) == FAILED)
	{
		if (cmd->previous)
		{
			close(cmd->previous->pipefd[0]);
			close(cmd->previous->pipefd[1]);
		}
		error_quit(shell, SYSCALL_ERROR, NULL);
	}
}
