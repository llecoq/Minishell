/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:34:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/20 13:59:21 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ambiguous_redirect(t_cmd *cmd, char *file_name)
{
	char	*ptr;

	ptr = file_name;
	if (cmd->redir.file_name != NULL && cmd->token_list->redir != IS_FILE)
	{
		if (file_name == NULL || (file_name && *file_name == '\0'))
		{
			free_set_null((void **)&ptr);
			return (AMBIGUOUS_REDIRECT);
		}
		while (*file_name)
		{
			if (*file_name == SPACE)
			{
				free_set_null((void **)&ptr);
				return (AMBIGUOUS_REDIRECT);
			}
			file_name++;
		}
		cmd->redir.file_name = ptr;
	}
	return (IS_VALID);
}
