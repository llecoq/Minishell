/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:41:28 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/23 12:07:29 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void	clear_memory(t_shell *shell)
{
	if (shell->env_list)
		ft_lstclear(&shell->env_list, del);
	if (shell->env_tab)
		free_set_null((void **)&shell->env_tab);
	if (shell->path)
		ft_lstclear(&shell->path, del);
	if (shell->cmd_array)
	{
		free_cmd_array(shell->cmd_array);
		free(shell->cmd_array);
		shell->cmd_array = NULL;
	}
	if (shell->user_dir)
		free_set_null((void **)&shell->user_dir);
	//dprintf(1, "pointer shell->cmd_array = %p\n", shell->cmd_array);
}