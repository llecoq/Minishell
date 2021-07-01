/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:11:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/01 14:07:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_list *env_list)
{
	size_t	len;

	len = 0;
	while (env_list)
	{
		if (env_list->variable == IS_SET)
			len++;
		env_list = env_list->next;
	}
	return (len);
}

void	store_path_list(t_shell *shell, char *path)
{
	char	**path_tab;
	char	*full_path;
	int		i;

	path_tab = ft_split(path, ':');
	i = -1;
	while (path_tab[++i])
	{
		full_path = ft_strjoin(path_tab[i], "/");
		free(path_tab[i]);
		ft_lstadd_back(&shell->path, ft_lstnew(full_path));
	}
	free(path_tab);
}

void	store_environment_list(t_shell *shell, char *const *env)
{
	while (*env)
		ft_lstadd_back(&shell->env_list, ft_lstnew(ft_strdup(*env++)));
}

// store the environment in a tab, by sending it a linked list.
// if the tab is already existing, it will free it then create a new one
// (to be used any time any time an export / unset is called)
// call env_size(t_list *env_list) for the size of the list
void	store_environment_tab(t_shell *shell, t_list *env_list, int len)
{
	if (shell->envp)
	{
		free(shell->envp);
		shell->envp = NULL;
	}
	shell->envp = calloc_sh(shell, sizeof(char *) * (len + 1));
	len = -1;
	while (env_list)
	{
		if (env_list->variable == IS_SET)
			shell->envp[++len] = env_list->content;
		env_list = env_list->next;
	}
}

int	store_environment(t_shell *shell, char *const *envp)
{
	store_environment_list(shell, envp);
	store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
	store_path_list(shell, getenv("PATH"));
	return (1);
}
