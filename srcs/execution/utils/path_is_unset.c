/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 16:03:20 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/06 17:30:13 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_is_not_absolute(char **argv, t_list **path_list)
{
	if (*argv[0] == '/' || ft_strncmp("./", *argv, 2) == 0)
	{
		ft_lstadd_back(path_list, ft_lstnew(NULL));
		errno = 0;
		return (0);
	}
	return (1);
}

int	path_is_unset(t_shell *shell, t_list **path_list)
{
	(*path_list) = shell->path;
	if ((*path_list) == NULL || (*path_list)->variable == IS_UNSET)
	{
		errno = ENOENT;
		exit_status = CMD_NOT_FOUND;
		return (1);
	}
	return (0);
}
