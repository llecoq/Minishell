/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:40:09 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 16:04:17 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_tokens_to_list(t_shell *shell, t_token *head, char	**word)
{
	t_token	*new_token;
	int		i;

	i = 1;
	while (word[i])
	{
		new_token = create_new_token(word[i], shell);
		turn_on_flag(ARG, new_token);
		add_token_tail(&head, new_token);
		i++;
	}
}

static void	print_current_argv(t_cmd *cmd)
{
	int				i;

	i = 0;
	while (cmd->argv[i])
	{
		ft_printf(1, "%s, ", cmd->argv[i]);
		i++;
	}
	ft_printf(1, "NULL");
	ft_printf(1, "\n");
}

void	print_argv(t_cmd *cmds_list)
{
	int				i;
	t_cmd			*cmd;

	i = 0;
	cmd = cmds_list;
	while (cmd)
	{
		ft_printf(1, "COMMAND #%d\n", i);
		print_current_argv(cmd);
		i++;
		cmd = cmd->next;
	}
}

void	erase_token(t_token **token, t_token **head, t_shell *shell)
{
	t_token	*prev;
	t_token	*next;

	prev = (*token)->previous;
	next = (*token)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->previous = prev;
	free((*token)->word);
	(*token)->word = NULL;
	free_set_null((void **)token);
	(*token) = next;
	if (prev == NULL)
		(*head) = (*token);
	(void)shell;
}

void	erase_cmd(t_token *cmd)
{
	t_token		*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_set_null((void **)&tmp->word);
		free_set_null((void **)&tmp);
	}
}
