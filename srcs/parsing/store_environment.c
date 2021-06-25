/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:11:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 12:56:17 by llecoq           ###   ########.fr       */
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

void	store_environment_list(t_shell *shell, const char **env)
{
	while (*env)
		ft_lstadd_back(&shell->env_list, ft_lstnew(ft_strdup(*env++)));
}

// store the environment in a tab, by sending it a linked list.
// if the tab is already existing, it will free it then create a new one
// (to be used any time any time an export / unset is called)
void	store_environment_tab(t_shell *shell, t_list *env_list, int len)
{
	if (shell->envp)
	{
		free(shell->envp);
		shell->envp = NULL;
	}
	shell->envp = calloc_sh(shell, sizeof(char *) * len + 1);
	if (!shell->envp)
		error_quit(shell, 0);
	len = -1;
	while (env_list)
	{
		shell->envp[++len] = env_list->content;
		env_list = env_list->next;
	}
}

int	store_environment(t_shell *shell, const char **envp)
{
	store_environment_list(shell, envp);
	store_environment_tab(shell, shell->env_list, ft_lstsize(shell->env_list));
	store_path_list(shell, getenv("PATH"));
	return (1);
}
