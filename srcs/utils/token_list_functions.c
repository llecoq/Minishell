/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:28:56 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/15 16:03:22 by abonnel          ###   ########.fr       */
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
		error_quit(shell, 0);
	new_token->word = ft_strdup(token);
	if (!(new_token->word))
	 	error_quit(shell, 0);
	new_token->next = NULL;
	new_token->previous = NULL;;
	return (new_token);
}

void	print_cmd_array(t_token **cmd_array, int flags)
{
	int				i;
	int				x;
	t_token			*cpy;

	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		x = 0;
		while (cpy)
		{
			ft_printf(1, "cmd[%d], ", i);
			if (flags == 1)
			{
				if (cpy->cmd)
					ft_printf(1, "flag : CMD, ");
				if (cpy->arg)
					ft_printf(1, "flag : ARG, ");
				if (cpy->redir)
					ft_printf(1, "flag : REDIR, ");
			}
			ft_printf(1, "token n*%d = |%s|\n", x, cpy->word);
			cpy = cpy->next;
			x++;
		}
		i++;
	}
}

void	erase_token(t_token **token, t_shell *shell)
{
	t_token 		*prev;
	t_token			*next;

	// if ((*token)->previous == NULL)
	// {
	// 	next = (*token)->next;
	// 	free_set_null((void **)token);
	// 	*token = next;
	// 	dprintf(1, "token = %p\n", *token);
	// 	(*token)->previous = NULL;
	// }
	// // else if ((*token)->next == NULL)
	// // {
		
	// // }
	// else
	// {
		prev = (*token)->previous; //si null
		next = (*token)->next;
		prev->next = next;
		next->previous = prev;
		free_set_null((void **)token);
		(*token) = next;
	// }
	(void)shell;
}

	// t_token		*tmp;
	// //!! si token est dernier token de pas sefault
	// tmp = *token;
	// *token = (*token)->previous;
	// (*token)->next = (*token)->next->next;
	// (*token)->next->previous = (*token);
	// free(tmp);
	// (void)shell;

	// t_token 		*prev;
	// t_token			*next;
	
	// //!! si pas de previous
	// if (!(*token)->previous)
	// {
	// 	next = (*token)->next;
	// 	free_set_null((void **)token);
	// 	*token = next;
	// 	(*token)->previous = NULL;
	// 	dprintf(1, "token->cmd = %d\n", (*token)->cmd);
	// }
	// else
	// {
	// 	prev = (*token)->previous; //si null
	// 	next = (*token)->next;
	// 	prev->next = next;
	// 	next->previous = prev;
	// 	free_set_null((void **)token);
	// }
	// (void)shell;
