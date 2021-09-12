/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:01:41 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/12 16:41:28 by llecoq           ###   ########.fr       */
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
	if (flag == SEMICOLON)
		cpy->redir = flag;
	else if (flag >= IS_REDIR)
		cpy->redir = flag;
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
