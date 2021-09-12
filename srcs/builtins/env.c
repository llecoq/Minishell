/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:41:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/12 15:49:06 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	search_for_changing_dir(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		if (argv[i] == '/' || argv[i] == '.')
			return (1);
	return (0);
}

int	process_env_args(char **argv)
{
	int		fd;
	int		ret;
	int		denied;
	char	buff;

	if (*argv[1] == '-')
		return (ILLEGAL_OPTION);
	denied = search_for_changing_dir(argv[1]);
	fd = open(argv[1], O_RDONLY);
	ret = read(fd, &buff, 1);
	close (fd);
	if (ret == -1 && denied == 1)
		return (PERMISSION_DENIED);
	if (fd > 1)
		return (NO_SUCH_FILE_OR_DIRECTORY);
	return (0);
}

int	ft_env(t_shell *shell, char **argv)
{
	int	fd;

	fd = redir_single_builtin_cmd("env", argv[0]);
	if (argv[1])
	{
		exit_status = process_env_args(argv);
		if (exit_status == ILLEGAL_OPTION)
			ft_printf(2, "env: illegal option -- %c\nusage: env\n", argv[1][1]);
		else if (exit_status == PERMISSION_DENIED)
			ft_printf(2, "env: %s: Permission denied\n", argv[1]);
		else if (exit_status == NO_SUCH_FILE_OR_DIRECTORY)
			ft_printf(2, "env: %s: No such file or directory\n", argv[1]);
		return (exit_status);
	}
	print_env(shell, fd);
	return (0);
}
