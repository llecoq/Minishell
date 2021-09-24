/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expand_file_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:22:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 16:14:01 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_for_file_name(t_cmd *cmd, t_token *token)
{
	while (token)
	{
		if (token->redir == IS_FILE)
		{
			cmd->redir.file_name = token->word;
			return (token->word);
		}
		token = token->next;
	}
	return (NULL);
}

char	*search_and_expand_file_name(t_shell *shell, t_cmd *cmd, t_token *tk)
{
	char	*file_name;
	char	*expanded_file_name;

	if (cmd->redir.file_name)
		return (cmd->redir.file_name);
	if (tk->redir == IS_FILE)
	{
		cmd->token_list = tk;
		return (NULL);
	}
	cmd->token_list = tk;
	file_name = search_for_file_name(cmd, tk);
	if (file_name == NULL)
		return (NULL);
	expanded_file_name = ft_strdup(file_name);
	replace_token_with_var(&expanded_file_name, shell);
	return (expanded_file_name);
}
