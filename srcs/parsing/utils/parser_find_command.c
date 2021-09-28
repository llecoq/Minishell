/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:49:52 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/28 15:32:41 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_builtin_function(char **argv, t_cmd *cmd)
{
	char	*cmd_name;

	if (argv == NULL)
		return (1);
	cmd_name = cmd->argv[0];
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		cmd->ft_builtin = &ft_cd;
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		cmd->ft_builtin = &ft_pwd;
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		cmd->ft_builtin = &ft_env;
	else if (ft_strncmp(cmd_name, "echo", 5) == 0)
		cmd->ft_builtin = &ft_echo;
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		cmd->ft_builtin = &ft_exit;
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		cmd->ft_builtin = &ft_unset;
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		cmd->ft_builtin = &ft_export;
	else
		cmd->ft_builtin = NULL;
	if (cmd->ft_builtin)
		return (1);
	return (0);
}
