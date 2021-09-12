/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:01:20 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/12 17:01:47 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_oldpwd(t_list **list, char **line)
{
	t_list	*new_elem;

	free(*line);
	*line = ft_strdup("OLDPWD=");
	new_elem = ft_lstnew(*line);
	new_elem->variable = IS_UNSET;
	ft_lstadd_back(list, new_elem);
}

static void	process_shell_level(char **line)
{
	int		shell_level;
	char	*new_shell_level;

	shell_level = ft_atoi(getenv("SHLVL"));
	new_shell_level = ft_itoa(shell_level + 1);
	free(*line);
	*line = ft_strjoin("SHLVL=", new_shell_level);
	free(new_shell_level);
}

void	store_list(t_list **list, char *const *env)
{
	char	*line;

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
				process_shell_level(&line);
			ft_lstadd_back(list, ft_lstnew(line));
			env++;
		}
	}
}
