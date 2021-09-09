/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:11:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/09 14:51:04 by llecoq           ###   ########.fr       */
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

	if (path == NULL)
		return ;
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

// void	add_oldpwd_to_list(t_list **list)
// {
// 	char	*line;

// 	line = ft_strdup("OLDPWD");
// 	ft_lstadd_back(list, ft_lstnew(line));
// }

void	process_oldpwd(t_list **list, char **line)
{
	t_list	*new_elem;

	free(*line);
	*line = ft_strdup("OLDPWD=");
	new_elem = ft_lstnew(*line);
	new_elem->variable = IS_UNSET;
	ft_lstadd_back(list, new_elem);
}

void	store_list(t_list **list, char *const *env)
{
	char	*line;
	char	*new_shell_level;
	int		shell_level;

	while (*env)
	{
		if (*env)
		{
			line = ft_strdup(*env);
			if (ft_strncmp(*env, "_=", 2) == 0)
			{
				free(line);
				line = ft_strdup("_=/usr/bin/env");
			}
			else if (ft_strncmp(*env, "OLDPWD=", 7) == 0)
			{
				process_oldpwd(list, &line);
				env++;
				continue ;
			}	
			else if (ft_strncmp(*env, "SHLVL=", 6) == 0)
			{
				shell_level = ft_atoi(getenv("SHLVL"));
				new_shell_level = ft_itoa(shell_level + 1);
				free(line);
				line = ft_strjoin("SHLVL=", new_shell_level);
				free(new_shell_level);
			}
			ft_lstadd_back(list, ft_lstnew(line));
			env++;
		}
	}
	// if (list_type == EXPORT_LIST)
	// 	add_oldpwd_to_list(list);
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
		if (ft_strncmp(env_list->content, "OLDPWD", 7) == 0)
			env_list->variable = IS_UNSET;
		if (env_list->variable == IS_SET)
			shell->envp[++len] = env_list->content;
		env_list = env_list->next;
	}
}

void	store_environment(t_shell *shell, char *const *envp)
{
	store_list(&shell->env_list, envp);
	store_list(&shell->export_list, envp);
	sort_alphabetically_list(&shell->export_list);
	store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
	store_path_list(shell, getenv("PATH"));
}
