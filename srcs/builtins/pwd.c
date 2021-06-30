/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 13:53:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 20:33:02 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// original pwd does not care if there is any arguments after the command
// it will only take into consideration an option (ex : -p)

int	ft_pwd(t_shell *shell, char **argv)
{
	char	*pwd;

	(void)shell;
	if (invalid_args_or_options(argv, "pwd"))
		return (-1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);		// fail
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);				// success
}
