/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:41:28 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/21 18:54:55 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_memory(t_shell *shell)
{
	if (shell->env_list)
		ft_lstclear(&shell->env_list, del);
	if (shell->env_tab)
	{
		free(shell->env_tab);
		shell->env_tab = NULL;
	}
	if (shell->path)
		ft_lstclear(&shell->path, del);
}
