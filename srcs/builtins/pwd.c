/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:53:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/24 15:19:53 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// original pwd does not care if there is any arguments after the command
// it will only take into consideration an option (ex : -p)

int	pwd(const char *path, char const **argv, char const **envp)
{
	char	*pwd;

	(void)path;
	(void)envp;
	if (argv[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2); // will maybe need to change that ?
		return (1);			// it returns zero if it succeeded and nonzero if it failed.
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);		// fail
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);				// success
}
