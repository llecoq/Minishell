/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:53:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/27 15:01:17 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// original pwd does not care if there is any arguments after the command
// it will only take into consideration an option (ex : -p)

int	ft_pwd(t_shell *shell, char **argv)
{
	char	*pwd;
	int		fd;

	(void)shell;
	fd = redir_single_builtin_cmd("pwd", argv[0]);
	if (invalid_args_or_options(argv, "pwd", PWD))
		return (-1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);		// fail
	if (ft_strncmp(pwd, "/", 2) == 0)
		ft_printf(fd, "//\n");
	else if (ft_strncmp(pwd, "/private", 8) == 0)
		ft_printf(fd, "%s\n", pwd + 8);
	else
		ft_printf(fd, "%s\n", pwd);
	free(pwd);
	return (0);				// success
}
