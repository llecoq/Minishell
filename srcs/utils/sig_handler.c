/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:12:40 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/15 17:06:29 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	// ft_printf(1, "\nsignum = %d", signum);
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);   // printf peut poser pb à cause du buffer
		rl_on_new_line(); // Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
		rl_replace_line("", 0); //Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
		rl_redisplay();	// Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == 15651)  // trouver CONTROL L
			printf("\e[1;1H\e[2J"); // clear le terminal
	// gerer control \    pour l'instant abort
}

void	get_signal(void)
{
	signal(SIGINT, sig_handler);  // control C
	signal(SIGQUIT, sig_handler);  // control + '\'
}
