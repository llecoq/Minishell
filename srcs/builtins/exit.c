/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:11:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/18 19:52:44 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dois traiter les args
int	ft_exit(t_shell *shell, char **argv)
{
	if (argv && ft_strncmp(argv[0], "exit", 5) == 0)
		ft_printf(1, "exit\n");
	if (argv == NULL) // si argv NULL, alors ft_exit called avec CTRL + D
	{
		// essayer de deplacer curseur avec termcaps ?
		// ft_putstr_fd("exit\n", 1);
		// printf("%c[2K", 27);   // ne marche
		// printf("\r");          // PAAAAAAAS
		// printf("%sexit\n", shell->user_dir);`
	}
	clear_memory(shell);
	exit(EXIT_SUCCESS);
}
