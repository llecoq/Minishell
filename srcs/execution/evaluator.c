/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:14:56 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 16:44:24 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipefds(t_cmd *cmd)
{
	close(cmd->pipefd[1]);
	if (cmd->previous)
		close(cmd->previous->pipefd[0]);
	if (!cmd->next)
		close(cmd->pipefd[0]);
	if (cmd->redir.from_heredoc >= EXISTENT)
		close(cmd->redir.from_heredoc);
}

int	evaluator(t_shell *shell, t_cmd *cmd, int nb_of_cmds)
{
	int		i;
	pid_t	pid;

	if (nb_of_cmds == 1 && find_builtin_function(cmd->argv, cmd))
		return (execute_single_builtin_cmd(shell, cmd, cmd->argv));
	i = -1;
	while (++i < nb_of_cmds && cmd)
	{
		create_pipe(shell, cmd);
		pid = fork();
		cmd->token_list = shell->cmd_array[i];
		if (pid == FAILED)
			error_quit(shell, SYSCALL_ERROR, NULL);
		else if (pid == CHILD_PROCESS)
			execution_child_process(shell, cmd);
		else if (pid >= PARENT_PROCESS)
			close_pipefds(cmd);
		cmd = cmd->next;
	}
	g_exit_status = last_child_status(pid);
	return (g_exit_status);
}
