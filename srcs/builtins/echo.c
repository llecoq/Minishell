/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:07:59 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/12 16:32:35 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// bash-3.2$ export VAR="   sansespaces"
// bash-3.2$ echo $VAR
// sansespaces
// echo trim les espaces devant

// lors d'ajout de flag non supportés comme -e -E, print un message d'erreur
// "-e not supported, usage = echo -p <msg>"
// ou simplement ne rien faire ?
// echo * fais un ls trimmé 
// int	ft_echo(t_shell *shell, char **argv)
// {
// 	char	*full_argument;
// 	int		flag;

// 	(void)shell;
// 	flag = 0;
// 	full_argument = NULL;
// 	if (argv[1] && ft_strncmp(argv[1], "-p", 3) == 0)
// 	{
// 		full_argument = join_args(argv, "-p");
// 		flag = 1;
// 	}
// 	else if (argv[1])
// 		full_argument = join_args(argv, NULL);
// 	if (full_argument)
// 	{
// 		ft_printf(1, "%s", full_argument);
// 		free_set_null((void **)&full_argument);
// 	}
// 	if (flag == 0);
// 		ft_putchar_fd('\n', 1);
// 	return (1);
// }
