/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:10:31 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 17:45:21 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_shell *shell, const char *name)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(name);
	i = -1;
	while (shell->envp[++i])
		if (ft_strncmp(shell->envp[i], name, len) == 0
			&& shell->envp[i][len] == '=')
			return (ft_strdup(shell->envp[i] + len + 1));
	return (NULL);
}
