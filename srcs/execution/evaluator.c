/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:14:56 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/18 17:07:34 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_file(t_shell *shell, t_list **path_list, char ***argv)
{
	char	**envp;
	t_file	file;

	envp = shell->envp;
	build_file_path(path_list, &file, argv);
	execve(file.file, (*argv), envp);
	if (file.arg_type == IS_PATH)
	{
		errno = ENOENT;
		error_quit(shell, SYSCALL_ERROR, (**argv));
	}
	free_set_null((void **)&file.tmp);
	free_set_null((void **)&file.file);
	(*path_list) = (*path_list)->next;
}

static void	execution_child_process(t_shell *shell, t_cmd *cmd)
{
	char	**argv;
	t_list	*path_list;

	argv = cmd->argv;
	create_redirection(shell, cmd, cmd->token_list);
	dup_input_redirection(shell, cmd);
	dup_output_redirection(shell, cmd);
	if (path_is_unset(shell, &path_list)
		&& path_is_not_absolute(argv, &path_list))
		error_quit(shell, SYSCALL_ERROR, *argv);
	// if cmd_is_builtin
	//		execute_builtin_and_exit
	while (path_list != NULL)
		execute_file(shell, &path_list, &argv);
	error_quit(shell, CMD_NOT_FOUND, *argv);
}

static void	close_pipefds(t_cmd *cmd)
{
	close(cmd->pipefd[1]);
	if (cmd->previous)
		close(cmd->previous->pipefd[0]);
	if (!cmd->next)
		close(cmd->pipefd[0]);
}

// ajouter le cas d'un seule commande (pas de fork si builtin)
void	evaluator(t_shell *shell, t_cmd *cmd, int nb_of_cmds)
{
	int		i;
	pid_t	pid[2048];

	// if (shell->nb_of_cmds == 1 && cmd_is_a_builtin(cmd->argv[0]))
	// 	return (execute_single_builtin_cmd(shell, cmd));
	i = -1;
	while (++i < nb_of_cmds)
	{
		create_pipe(shell, cmd);
		pid[i] = fork();
		cmd->token_list = shell->cmd_array[i];
		if (pid[i] == FAILED)
			error_quit(shell, SYSCALL_ERROR, NULL);
		else if (pid[i] == CHILD_PROCESS)
			execution_child_process(shell, cmd);
		else if (pid[i] >= PARENT_PROCESS)
			close_pipefds(cmd);
		cmd = cmd->next;
	}
	errno = last_child_status(pid[i - 1]);
}
