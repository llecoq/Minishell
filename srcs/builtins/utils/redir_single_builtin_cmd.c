/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_single_builtin_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:34:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/20 18:41:07 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_single_builtin_cmd(char *cmd_name, char *argv)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (ft_strncmp(cmd_name, argv, ft_strlen(cmd_name)) != 0)
	{
		fd = ft_atoi(argv);
		free (argv);
	}
	return (fd);
}
