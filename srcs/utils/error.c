/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:25:16 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/20 15:27:55 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// revoir valeur de retour erreur
// $? should expand to the exit status of the most recently executed foreground
// pipeline.
void	error_quit(t_shell *shell, int error_type, char *str)
{
	if (error_type == CMD_NOT_FOUND)
	{
		errno = CMD_NOT_FOUND;
		ft_printf(2, "minishell: %s: command not found\n", str);
	}
	if (error_type == SYSCALL_ERROR && str)
	{
		ft_printf(2, "minishell: %s: %s\n", str, strerror(errno));
		if (errno == ENOENT && exit_status == CMD_NOT_FOUND)
			errno = CMD_NOT_FOUND;
	}
	if (error_type == IS_A_DIRECTORY)
	{
		errno = IS_A_DIRECTORY;
		ft_printf(2, "minishell: %s: is a directory\n", str);
	}
	if (error_type == FILENAME_ARGUMENT_REQUIRED)
	{
		errno = FILENAME_ARGUMENT_REQUIRED;
		ft_printf(STDERR_FILENO, "minishell: .: filename argument required\n\
.: usage: . filename [arguments]\n");
	}
	if (error_type == AMBIGUOUS_REDIRECT)
	{
		errno = 1;
		ft_printf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n", str);
	}
	clear_memory(shell);
	exit(errno);
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
	// if (error_type == 0) //errno pour les built-in 
	// 	ft_printf(2, "%s\n", strerror(errno));
	if (error_type == NO_CLOSING_QUOTE)
	{
		ft_printf(2, "minishell: unexpected EOF while looking for matching\
 `''\n");
		ft_printf(2, "minishell: syntax error: unexpected end of file");
	}
	else if (error_type == NOTHING_AFTER_REDIR
		|| error_type == NOTHING_BEFORE_REDIR)
	{
		exit_status = 258;
		ft_printf(2, "minishell: syntax error near unexpected token `%s'", str);
	}
	ft_printf(2, "\n");
	clear_nonessential_memory(shell);
	free_split_cmds_by_semicolons(shell);
	//must stop current command and go back to prompt
}

void	error(t_shell *shell, int error_type, char *str)
{
	if (error_type == SYSCALL_ERROR && str)
	{
		exit_status = errno;
		ft_printf(2, "minishell: %s: %s\n", str, strerror(errno));
		return ;
	}
	if (error_type == AMBIGUOUS_REDIRECT)
	{
		exit_status = 1;
		ft_printf(2, "minishell: %s: ambiguous redirect\n", str);
	}
	if (error_type == 0) //errno pour les built-in 
		ft_printf(2, "%s\n", strerror(errno));
	else if (error_type == REDIR_ISNT_1_WORD)
		ft_printf(2, "minishell: %s: ambiguous redirect\n", str);
	else if (error_type == CANT_OPEN_FILE)
		ft_printf(2, "minishell: %s: %s\n", str, strerror(errno));
	else if (error_type == CMD_NOT_FOUND)
		ft_printf(2, "minishell: %s: command not found\n", str);
	else if (error_type == FILE_IS_DIR)
		ft_printf(2, "minishell: %s: Is a directory\n", str);
	(void)shell;
	//must stop current command and go back to prompt
}
