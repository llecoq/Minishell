/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:10:35 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 15:24:51 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_failed(t_cmd *cmd)
{
	if (g_exit_status == 1 && cmd && ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (1);
	return (0);
}

static int	syntax_error(t_shell *shell)
{
	if (shell->cmds_list == NULL)
		return (1);
	return (0);
}

void	process_input(t_shell *shell, int flag)
{		
	t_list	*split_cmds;

	split_cmds = split_by_semicolons(shell, shell->input);
	shell->split_cmds_by_semicolons = split_cmds;
	if (flag == PROMPT)
		free_set_null((void **)&shell->input);
	while (split_cmds)
	{
		tokenize(shell, split_cmds->content);
		if (shell->cmd_array == NULL)
			return ;
		parse(shell);
		if (&shell->cmd_array[0])
			g_exit_status = evaluator(shell, shell->cmds_list, \
			shell->nb_of_cmds);
		if (exit_failed(shell->cmds_list) || syntax_error(shell))
			break ;
		clear_nonessential_memory(shell);
		split_cmds = split_cmds->next;
	}
	ft_lstclear(&shell->split_cmds_by_semicolons, del);
}
