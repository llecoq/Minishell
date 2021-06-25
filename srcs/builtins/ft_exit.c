/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:11:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 12:58:47 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, int i)
{
	if (i == 1)
	{
		// essayer de deplacer curseur avec termcaps ?
		// write(0, "exit\n", 5);
		// ft_putstr_fd("exit\n", 1);
		// printf("%c[2K", 27);   // ne marche
		// printf("\r");          // PAAAAAAAS
		// printf("%sexit\n", shell->user_dir);`
	}
	clear_memory(shell);
	exit(EXIT_SUCCESS);
}
