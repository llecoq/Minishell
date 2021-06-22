/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_typeor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:25:16 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/18 15:28:00 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_quit(t_shell *shell, int error_type)
{
	if (error_type == 0) //syscall errors
		printf("%s\n", strerror(errno));
	// else if (error_type == 1)
	// 	dprintf(1, "");
	// else if (error_type == 2)
	// 	dprintf(1, "");
	// else if (error_type == 3)
	// 	dprintf(1, "");
	// else if (error_type == 4)
	// 	dprintf(1, "");
	// else if (error_type == 5)
	// 	dprintf(1, "");
	// else if (error_type == 6)
	// 	dprintf(1, "");
	clear_memory(shell);
	exit(EXIT_FAILURE);
}

void	error(t_shell *shell, int error_type)
{
	if (error_type == 0) //syscall errors
		printf("%s\n", strerror(errno));
	else if (error_type == NO_CLOSING_QUOTE)
		dprintf(1, "minishell: unexpected EOF while looking for matching `''\n\
		minishell: syntax error: unexpected end of file"); //!!alignement printf
	// else if (error_type == 2)
	// 	dprintf(1, "");
	// else if (error_type == 3)
	// 	dprintf(1, "");
	// else if (error_type == 4)
	// 	dprintf(1, "");
	// else if (error_type == 5)
	// 	dprintf(1, "");
	// else if (error_type == 6)
	// 	dprintf(1, "");
	dprintf(1, "\n");
	clear_memory(shell);
	//must stop current command and go back to prompt
}