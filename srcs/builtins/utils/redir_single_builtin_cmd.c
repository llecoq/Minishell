/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_single_builtin_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:34:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 16:44:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_single_builtin_cmd(char *cmd_name, char *arg)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (ft_strncmp(cmd_name, arg, ft_strlen(cmd_name)) != 0)
	{
		fd = ft_atoi(arg);
		free (arg);
	}
	return (fd);
}
