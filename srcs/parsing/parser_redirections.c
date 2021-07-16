/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:21:43 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/16 12:25:15 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---------------------------------------------------------------------------*/
/*-------- CREATE AND CHECKS REDIRECTIONS -----------------------------------*/
/*---------------------------------------------------------------------------*/

int	redir_is_one_word(char *token, t_shell *shell)
{
	int			i;
	char		*token_with_var;

	token_with_var = process_variables(token, shell);
	if (token_with_var == NULL || token_with_var[0] == '\0')
	{
		free(token_with_var);
		return (0);
	}
	i = 0;
	while (token_with_var[i])
	{
		if (token_with_var[i] == ' ')
		{
			free(token_with_var);	
			return (0);
		}
		i++;
	}
	free(token_with_var);
	return (1);
}

//When entering, token is the redirection SIGN
static int	create_redirection_file(t_token *token, t_shell *shell)
{
	int			mode;
	int			fd;
	t_token		*file_token;

	mode = is_redirection(token->word, 0);
	file_token = token->next;
	replace_token_with_var(&file_token->word, shell);
	fd = 0;
	//testé : pas besoin d'un absolute path pour open()
	if (mode == APPEND)
		fd = open(file_token->word, O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (mode == REDIR)
		fd = open(file_token->word, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (mode == INREDIR)
		fd = open(file_token->word, O_RDONLY);
	if (fd < 0)
	{
		error(shell, CANT_OPEN_FILE, file_token->word);
		return (CANT_OPEN_FILE);
	}
	else
		token->fd = fd;
	return (1);
}

static int	establish_redirection(t_token *token, t_shell *shell)
{
	if (!redir_is_one_word(token->next->word, shell))
	{
		error(shell, REDIR_ISNT_1_WORD, token->next->word);
		return (CMD_IS_WRONG);
	}
	if (create_redirection_file(token, shell) == CANT_OPEN_FILE)
		return (CMD_IS_WRONG);
	return (1);
}

int	check_and_create_redirections(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;
	
	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{
			//enter on the redir sign except pipe
			if (token->redir == 1 && is_redirection(token->word, 0) != PIPE)
			{
				if (establish_redirection(token, shell) == CMD_IS_WRONG)
				{
					erase_current_cmd(cmd_array, i, shell);
					i--;//pour qu'il check bien la commande qui a pris la place
					break;
				}
				token = token->next;
			}
			token = token->next;
		}
		i++;
	}
	return (1);//a changer
}
