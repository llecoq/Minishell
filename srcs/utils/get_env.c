/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:10:31 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 12:11:22 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//    The getenv() function searches the environment list to find the
//    environment variable name, and returns a pointer to the
//    corresponding value string.
//    As typically implemented, getenv() returns a pointer to a string
//    within the environment list.  The caller must take care not to
//    modify this string, since that would change the environment of
//    the process.
char	*get_env(t_shell *shell, const char *name)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(name);
	i = -1;
	while (shell->envp[++i])
		if (ft_strncmp(shell->envp[i], name, len) == 0
			&& shell->envp[i][len] == '=')
			return (ft_strchr(shell->envp[i], '=') + 1);
	return (NULL);
}
