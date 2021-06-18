/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:11:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 16:44:42 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	store_environment_list(t_shell *shell, char **env)
{
	int	len;

	len = -1;
	while (env[++len])
		ft_lstadd_back(&shell->path, ft_lstnew(ft_strdup(env[len])));
	return (len);
}

int	store_environment_tab(t_shell *shell, t_list *path, int len)
{
	if (shell->env)
	{
		free(shell->env);
		shell->env = NULL;
	}
	shell->env = calloc_sh(shell, sizeof(char *) * len + 1);
	shell->env[len] = 0;
	len = -1;
	while (path)
	{
		shell->env[++len] = path->content;
		path = path->next;
	}
	return (1);
}

int	store_environment(t_shell *shell, char **env)
{
	int	len;

	len = store_environment_list(shell, env);
	if (!store_environment_tab(shell, shell->path, len))
		error_quit(shell, 0);
	return (1);
}