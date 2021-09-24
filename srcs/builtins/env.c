/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:41:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 15:48:03 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum	e_env
{
	ILLEGAL_OPTION = 1,
	PERMISSION_DENIED = 126,
	NO_SUCH_FILE_OR_DIRECTORY = 127,
};

// when unset and exported again, all the variables already existing in envp
// are coming back to the original position in the list
// We need to print it from the tab, because in the linked list there is still
// elements that are unset and should not be printed
void	print_env(t_shell *shell, int fd)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
		ft_printf(fd, "%s\n", (char *)shell->envp[i]);
}

static int	search_for_changing_dir(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		if (argv[i] == '/' || argv[i] == '.')
			return (1);
	return (0);
}

static int	process_env_args(char **argv)
{
	int		fd;
	int		denied;

	if (*argv[1] == '-')
		return (ILLEGAL_OPTION);
	denied = search_for_changing_dir(argv[1]);
	fd = open(argv[1], O_RDONLY);
	close (fd);
	if (fd > 0 && denied == 1)
		return (PERMISSION_DENIED);
	if (fd > 0 || argv[1])
		return (NO_SUCH_FILE_OR_DIRECTORY);
	return (0);
}

int	ft_env(t_shell *shell, char **argv)
{
	int	fd;

	fd = redir_single_builtin_cmd("env", argv[0]);
	if (argv[1])
	{
		g_exit_status = process_env_args(argv);
		if (g_exit_status == ILLEGAL_OPTION)
			ft_printf(2, "env: illegal option -- %c\nusage: env\n", argv[1][1]);
		else if (g_exit_status == PERMISSION_DENIED)
			ft_printf(2, "env: %s: Permission denied\n", argv[1]);
		else if (g_exit_status == NO_SUCH_FILE_OR_DIRECTORY)
			ft_printf(2, "env: %s: No such file or directory\n", argv[1]);
		return (g_exit_status);
	}
	print_env(shell, fd);
	if (fd > 2)
		close(fd);
	return (EXIT_SUCCESS);
}
