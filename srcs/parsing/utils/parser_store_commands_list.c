/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_store_commands_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:34:53 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/17 16:55:11 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_redir(t_cmd *cmd)
{
	cmd->redir.file_name = NULL;
	cmd->redir.from_heredoc = NONEXISTENT;
	cmd->redir.into_file = NONEXISTENT;
	cmd->redir.into_stdin = NONEXISTENT;
	cmd->redir.from_file = NONEXISTENT;
}

static t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

static t_cmd	*new_cmd(t_shell *shell)
{
	t_cmd	*new_elem;

	new_elem = malloc(sizeof(t_cmd));
	if (!new_elem)
		error_quit(shell, SYSCALL_ERROR, NULL);
	new_elem->token_list = NULL;
	new_elem->ft_builtin = NULL;
	new_elem->argv = NULL;
	new_elem->next = NULL;
	new_elem->previous = NULL;
	init_redir(new_elem);
	return (new_elem);
}

static void	addback_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (*list)
	{
		last_elem = last_cmd(*list);
		last_elem->next = new;
		new->previous = last_elem;
	}
	else
		*list = new;
}

void	create_empty_cmds_list(t_shell *shell, int nb_of_cmds)
{
	int	i;

	i = 0;
	while (i < nb_of_cmds)
	{
		addback_cmd(&shell->cmds_list, new_cmd(shell));
		i++;
	}
}
