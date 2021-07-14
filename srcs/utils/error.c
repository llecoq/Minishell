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
		ft_printf(2, "%s\n", strerror(errno));
	// else if (error_type == 1)
	// 	ft_printf(2, "");
	// else if (error_type == 2)
	// 	ft_printf(2, "");
	// else if (error_type == 3)
	// 	ft_printf(2, "");
	// else if (error_type == 4)
	// 	ft_printf(2, "");
	// else if (error_type == 5)
	// 	ft_printf(2, "");
	// else if (error_type == 6)
	// 	ft_printf(2, "");
	clear_memory(shell);
	exit(EXIT_FAILURE);
}


/*
For NOTHING_AFTER_REDIR

bash-3.2$ ls -la | wc |
> bash: syntax error: unexpected end of file
--> I CHOSE the other error msg bc "unexpected end of file"
happens bc of multiline that we do not have to handle
*/
void	err_clear(t_shell *shell, int error_type, char *str)
{
	if (error_type == 0) //errno pour les built-in 
		ft_printf(2, "%s\n", strerror(errno));
	else if (error_type == NO_CLOSING_QUOTE)
	{
		ft_printf(2, "minishell: unexpected EOF while looking for matching `''\n");
		ft_printf(2, "minishell: syntax error: unexpected end of file");
	}
	else if (error_type == NOTHING_AFTER_REDIR)
		ft_printf(2, "minishell: syntax error near unexpected token %s", str);
	// else if (error_type == 4)
	// 	ft_printf(2, "");
	// else if (error_type == 5)
	// 	ft_printf(2, "");
	// else if (error_type == 6)
	// 	ft_printf(2, "");
	ft_printf(2, "\n");
	clear_nonessential_memory(shell);
	//must stop current command and go back to prompt
}

void	error(t_shell *shell, int error_type, char *str)
{
	if (error_type == 0) //errno pour les built-in 
		ft_printf(2, "%s\n", strerror(errno));
	else if (error_type == REDIR_ISNT_1_WORD)
		ft_printf(2, "minishell: %s: ambiguous redirect", str);
	// else if (error_type == 4)
	// 	ft_printf(2, "");
	// else if (error_type == 5)
	// 	ft_printf(2, "");
	// else if (error_type == 6)
	// 	ft_printf(2, "");
	ft_printf(2, "\n");
	(void)shell;
	//must stop current command and go back to prompt
}