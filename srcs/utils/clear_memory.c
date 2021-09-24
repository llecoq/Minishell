/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:41:28 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 16:05:32 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_cmds_by_semicolons(t_shell *shell)
{
	if (shell->split_cmds_by_semicolons)
		ft_lstclear(&shell->split_cmds_by_semicolons, del);
}

void	free_cmd_array(t_token **cmd_array)
{
	t_token		*tmp;
	int			i;

	i = 0;
	while (cmd_array[i])
	{
		while (cmd_array[i])
		{
			tmp = cmd_array[i]->next;
			free_set_null((void **)&cmd_array[i]->word);
			free_set_null((void **)&cmd_array[i]);
			cmd_array[i] = tmp;
		}
		i++;
	}
}

static void	free_cmd_list(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->argv)
			free_set_null((void **)&(*lst)->argv);
		free((*lst));
		(*lst) = NULL;
		*lst = tmp;
	}
	*lst = NULL;
}

void	clear_nonessential_memory(t_shell *shell)
{
	if (shell->cmd_array)
	{
		free_cmd_array(shell->cmd_array);
		free(shell->cmd_array);
		shell->cmd_array = NULL;
	}
	if (shell->cmds_list)
		free_cmd_list(&shell->cmds_list);
}

void	clear_memory(t_shell *shell)
{
	if (shell->env_list)
		ft_lstclear(&shell->env_list, del);
	if (shell->export_list)
		ft_lstclear(&shell->export_list, del);
	if (shell->envp)
		free_set_null((void **)&shell->envp);
	if (shell->path)
		ft_lstclear(&shell->path, del);
	if (shell->user_dir)
		free_set_null((void **)&shell->user_dir);
	if (shell->cmds_list)
		free_cmd_list(&shell->cmds_list);
	clear_nonessential_memory(shell);
	rl_clear_history();
}
