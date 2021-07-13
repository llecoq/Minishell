/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:28:56 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/13 16:46:00 by llecoq           ###   ########.fr       */
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