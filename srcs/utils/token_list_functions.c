/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:28:56 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 16:04:52 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_previous_pointers(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (head)
	{
		if (head->next)
			head->next->previous = head;
		head = head->next;
	}
	head = tmp;
}

t_token	*return_tail_token(t_token *token_lst)
{
	if (token_lst)
		while (token_lst->next)
			token_lst = token_lst->next;
	return (token_lst);
}

void	add_token_tail(t_token **head, t_token *new_token)
{
	t_token	*last_token;

	last_token = NULL;
	if (*head)
	{
		last_token = return_tail_token(*head);
		last_token->next = new_token;
		new_token->previous = last_token;
	}
	else
		*head = new_token;
}

t_token	*create_new_token(char *token, t_shell *shell)
{
	t_token			*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!(new_token))
		error_quit(shell, SYSCALL_ERROR, NULL);
	new_token->word = ft_strdup(token);
	if (!(new_token->word))
		error_quit(shell, SYSCALL_ERROR, NULL);
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

char	*find_redir_type(int flag)
{
	char	*redir_type;

	redir_type = NULL;
	if (flag == PIPE)
		redir_type = "PIPE";
	else if (flag == TRUNC)
		redir_type = "TRUNC";
	else if (flag == APPEND)
		redir_type = "APPEND";
	else if (flag == INPUT_REDIR)
		redir_type = "INPUT_REDIR";
	else if (flag == HEREDOC)
		redir_type = "HEREDOC";
	else if (flag == IS_FILE)
		redir_type = "IS_FILE";
	else if (flag == STOP_VALUE)
		redir_type = "STOP_VALUE";
	return (redir_type);
}
