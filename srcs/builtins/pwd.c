/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:53:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/12 16:37:53 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// original pwd does not care if there is any arguments after the command
// it will only take into consideration an option (ex : -p)
int	ft_pwd(t_shell *shell, char **argv)
{
	char	*pwd;
	int		fd;

	fd = redir_single_builtin_cmd("pwd", argv[0]);
	if (invalid_args_or_options(argv, "pwd", PWD))
		return (1);
	pwd = get_env(shell, "PWD");
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		ft_printf(fd, "%s\n", pwd);
		free(pwd);
		return (0);
	}
	if (ft_strncmp(pwd, "/private", 8) == 0)
		ft_printf(fd, "%s\n", pwd + 8);
	else
		ft_printf(fd, "%s\n", pwd);
	return (0);
}
