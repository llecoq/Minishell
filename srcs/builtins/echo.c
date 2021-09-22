/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:07:59 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/22 13:12:11 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash-3.2$ export VAR="   sansespaces"
// bash-3.2$ echo $VAR
// sansespaces
// echo trim les espaces devant

// lors d'ajout de flag non supportés comme -e -E, print un message d'erreur
// "-e not supported, usage = echo -p <msg>"
// ou simplement ne rien faire ?
// echo * fais un ls trimmé 
static void	process_n_flag(char ***argv, int *flag)
{
	int	i;

	while (**argv)
	{
		if (ft_strncmp((**argv), "-n", 2) == 0)
		{
			i = 2;
			while ((**argv)[i] && (**argv)[i] == 'n')
				i++;
			if ((**argv)[i] == '\0')
			{
				(*argv)++;
				*flag = 1;
			}
			else
				return ;
		}
		else
			return ;
	}
}

int	ft_echo(t_shell *shell, char **argv)
{
	int	flag;
	int	fd;

	(void)shell;
	flag = 0;
	fd = redir_single_builtin_cmd("echo", argv[0]);
	argv++;
	process_n_flag(&argv, &flag);
	while (*argv)
	{
		ft_printf(fd, "%s", *argv);
		argv++;
		if (*argv)
			ft_putchar_fd(' ', fd);
	}
	if (flag == 0)
		ft_putchar_fd('\n', fd);
	if (fd > 2)
		close(fd);
	return (EXIT_SUCCESS);
}
