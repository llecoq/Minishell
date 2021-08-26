/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:14:56 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/26 18:18:16 by llecoq           ###   ########.fr       */
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

static void	execute_builtin_and_exit(t_shell *shell, t_cmd *cmd, char **argv)
{
	cmd->ft_builtin(shell, argv);
	ft_exit(shell, argv);
}

static int	path_is_a_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		dir = opendir(++path);
		if (dir == NULL)
			return (IS_NOT_A_DIRECTORY);
	}
	closedir(dir);
	return (IS_A_DIRECTORY);
}

static void	execution_child_process(t_shell *shell, t_cmd *cmd)
{
	char	**argv;
	t_list	*path_list;

	argv = cmd->argv;
	create_redirection(shell, cmd, cmd->token_list);
	dup_input_redirection(shell, cmd);
	dup_output_redirection(shell, cmd);
	if (find_builtin_function(cmd->argv[0], cmd))
		return (execute_builtin_and_exit(shell, cmd, cmd->argv));
	if (path_is_unset(shell, &path_list)
		&& path_is_not_absolute(argv, &path_list))
		error_quit(shell, SYSCALL_ERROR, *argv);
	if (ft_strncmp(*argv, ".", 2) == 0)
		error_quit(shell, FILENAME_ARGUMENT_REQUIRED, NULL);
	if (ft_strncmp(*argv, "..", 3) == 0)
		error_quit(shell, CMD_NOT_FOUND, "..");
	if (path_is_a_directory(*argv))
		error_quit(shell, IS_A_DIRECTORY, *argv);
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

static int	execute_single_builtin_cmd(t_shell *shell, t_cmd *cmd, char **argv)
{
	create_redirection(shell, cmd, cmd->token_list);
	if (cmd->redir.from_file >= EXISTENT)
		close(cmd->redir.from_file);
	else if (cmd->redir.from_heredoc >= EXISTENT)
		close(cmd->redir.from_heredoc);
	if (cmd->redir.into_file >= EXISTENT)
		*argv = ft_itoa(cmd->redir.into_file);
	return (cmd->ft_builtin(shell, argv));
}

int	evaluator(t_shell *shell, t_cmd *cmd, int nb_of_cmds)
{
	int		i;
	pid_t	pid;

	if (nb_of_cmds == 1 && find_builtin_function(cmd->argv[0], cmd))
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
	exit_status = last_child_status(pid);
	return (exit_status);
}
