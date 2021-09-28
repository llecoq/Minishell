/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:19:59 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 15:38:10 by llecoq           ###   ########.fr       */
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

static void	error_management(t_shell *shell, char **argv, t_list **path_list)
{
	if (path_is_unset(shell, path_list)
		&& path_is_not_absolute(argv, path_list))
		error_quit(shell, SYSCALL_ERROR, *argv);
	if (ft_strncmp(*argv, ".", 2) == 0)
		error_quit(shell, FILENAME_ARGUMENT_REQUIRED, NULL);
	if (ft_strncmp(*argv, "..", 3) == 0)
		error_quit(shell, CMD_NOT_FOUND, "..");
}

void	execution_child_process(t_shell *shell, t_cmd *cmd)
{
	char	**argv;
	t_list	*path_list;

	argv = cmd->argv;
	create_redirection(shell, cmd, cmd->token_list, CHILD_PROCESS);
	dup_input_redirection(shell, cmd);
	dup_output_redirection(shell, cmd);
	if (find_builtin_function(cmd->argv, cmd))
		return (execute_builtin_and_exit(shell, cmd, cmd->argv));
	error_management(shell, argv, &path_list);
	if (path_is_a_directory(*argv))
		error_quit(shell, IS_A_DIRECTORY, *argv);
	while (path_list != NULL)
		execute_file(shell, &path_list, &argv);
	error_quit(shell, CMD_NOT_FOUND, *argv);
}
