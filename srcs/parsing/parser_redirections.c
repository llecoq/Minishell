/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:21:43 by abonnel           #+#    #+#             */
/*   Updated: 2021/08/17 14:43:23 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*---------------------------------------------------------------------------*/
// /*-------- CREATE AND CHECKS REDIRECTIONS -----------------------------------*/
// /*---------------------------------------------------------------------------*/

// int	redir_is_one_word(char *token, t_shell *shell)
// {
// 	int			i;
// 	char		*token_with_var;

// 	token_with_var = process_variables(token, shell);
// 	if (token_with_var == NULL || token_with_var[0] == '\0')
// 	{
// 		free(token_with_var);
// 		return (0);
// 	}
// 	i = 0;
// 	while (token_with_var[i])
// 	{
// 		if (token_with_var[i] == ' ')
// 		{
// 			free(token_with_var);	
// 			return (0);
// 		}
// 		i++;
// 	}
// 	free(token_with_var);
// 	return (1);
// }

// //open() does not need an absolute path, it acts in the current working dir

// //RDWR instead of WRONLY otherwise we get an error when doing read() on the
// //file to check if it is a directory
// static void	open_fd(int mode, int *fd, char *file_name)
// {
// 	if (mode == APPEND)
// 		*fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
// 	else if (mode == REDIR)
// 		*fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	else if (mode == INREDIR)
// 		*fd = open(file_name, O_RDONLY);
// }

// static int	check_fd_errors(int fd, t_shell *shell, char *word, int mode)
// {
// 	char		*buf[2];
	
// 	if (fd < 0)
// 	{
// 		error(shell, CANT_OPEN_FILE, word);
// 		return (CANT_OPEN_FILE);
// 	}
// 	else if (read(fd, buf, 1) < 0)
// 	{
// 		if (mode == INREDIR)
// 			error(shell, FILE_IS_DIR, "stdin");
// 		else
// 			error(shell, CANT_OPEN_FILE, word);
// 		close(fd);
// 		return (CANT_OPEN_FILE);
// 	}
// 	return (0);
// }

// //When entering, token is the redirection SIGN
// static int	create_redirection_file(t_token *token, t_shell *shell)
// {
// 	int			mode;
// 	int			fd;
// 	t_token		*file_token;

// 	fd = 0;
// 	file_token = token->next;
// 	mode = is_redirection(token->word, 0);
// 	replace_token_with_var(&file_token->word, shell);
// 	open_fd(mode, &fd, file_token->word);
// 	if (check_fd_errors(fd, shell, file_token->word, mode) == CANT_OPEN_FILE)
// 		return (CANT_OPEN_FILE);
// 	else
// 		token->fd = fd;
// 	return (1);
// }

// static int	establish_redirection(t_token *token, t_shell *shell)
// {
// 	if (is_redirection(token->word, 0) == HEREDOC)
// 		return (1);
// 	if (!redir_is_one_word(token->next->word, shell))
// 	{
// 		error(shell, REDIR_ISNT_1_WORD, token->next->word);
// 		return (CMD_IS_WRONG);
// 	}
// 	if (create_redirection_file(token, shell) == CANT_OPEN_FILE)
// 		return (CMD_IS_WRONG);
// 	return (1);
// }

// //protections contre cmd_array->error inutile pour le moment car aucune cmd n'a
// //pu emettre d'erreur mais au cas ou remaniement du code plus tard
// //Doesn't do anything for HEREDOC -> HEREDOC can be several words it will not
// //raise an error and VARS are not expanded :
// //cat << $VAR	->the word to stop the input will be $VAR as a string literal
// void	check_and_create_redirections(t_token **cmd_array, t_shell *shell)
// {
// 	int			i;
// 	t_token		*token;
	
// 	i = 0;
// 	while (cmd_array[i])
// 	{
// 		if (cmd_array[i]->error == 0)
// 			token = cmd_array[i];
// 		else
// 			token = NULL;
// 		while (token)
// 		{
// 			if (token->redir == 1 && is_redirection(token->word, 0) != PIPE)
// 			{
// 				if (establish_redirection(token, shell) == CMD_IS_WRONG)
// 				{
// 					cmd_array[i]->error = 1;
// 					break;
// 				}
// 				token = token->next;
// 			}
// 			token = token->next;
// 		}
// 		i++;
// 	}
// }
