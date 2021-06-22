/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:11:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/21 19:15:23 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_path_list(t_shell *shell, char *path)
{
	char	**path_tab;
	char	**tmp;

	path_tab = ft_split(path, ':');
	tmp = path_tab;
	while (*path_tab)
		ft_lstadd_back(&shell->path, ft_lstnew(*path_tab++));
	free(tmp);
}

void	store_environment_list(t_shell *shell, char **env)
{
	while (*env)
		ft_lstadd_back(&shell->env_list, ft_lstnew(ft_strdup(*env++)));
}

void	store_environment_tab(t_shell *shell, t_list *env_list, int len)
{
	if (shell->env_tab)
	{
		free(shell->env_tab);
		shell->env_tab = NULL;
	}
	shell->env_tab = calloc_sh(shell, sizeof(char *) * len + 1);
	if (!shell->env_tab)
		error_quit(shell, 0);
	len = -1;
	while (env_list)
	{
		shell->env_tab[++len] = env_list->content;
		env_list = env_list->next;
	}
}

int	store_environment(t_shell *shell, char **env_tab)
{
	store_environment_list(shell, env_tab);
	store_environment_tab(shell, shell->env_list, ft_lstsize(shell->env_list));
	store_path_list(shell, getenv("PATH"));
	return (1);
}
