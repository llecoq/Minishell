/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:28:56 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/22 11:34:25 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*return_tail_token(t_token *token_lst)
{
	if (token_lst)
		while (token_lst->next)
			token_lst = token_lst->next;
	return (token_lst);
}

void	add_token_tail(t_token **head, t_token *new_token)
{
	if (*head)
		return_tail_token(*head)->next = new_token;
	else
		*head = new_token;
}

t_token	*create_new_token(char *token, t_shell *shell)
{
	t_token			*new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!(new_token))
		error_quit(shell, 0);
	new_token->word = (char *)calloc(ft_strlen(token), sizeof(char));
	if (!(new_token->word))
		error_quit(shell, 0);
	new_token->word = token;
	new_token->next = NULL;
	return (new_token);
} // VERIFY THAT OUTSIDE OF THIS FUNCTION new_token->word is set