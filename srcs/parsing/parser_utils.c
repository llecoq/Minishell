/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:01:41 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/16 12:25:23 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	turn_on_flag(int flag, t_token *cpy)
{
	if (flag == CMD)
		cpy->cmd = 1;
	else
		cpy->cmd = 0;
	if (flag == ARG)
		cpy->arg = 1;
	else
		cpy->arg = 0;
	if (flag == REDIR)
		cpy->redir = 1;
	else
		cpy->redir = 0;
}

void	erase_current_cmd(t_token **cmd_array, int i, t_shell *shell)
{
	t_token		*to_erase;

	to_erase = cmd_array[i];
	while (cmd_array[i])
	{
		cmd_array[i] = cmd_array[i + 1];
		i++;
	}
	erase_cmd(to_erase);
	(void)shell;
}