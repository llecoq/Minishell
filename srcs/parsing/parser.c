/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:51:02 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_word_is_cmd_flag(t_token **cmd_array)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->arg == 1)
			{
				turn_on_flag(CMD, token);
				break ;
			}
			token = token->next;
		}
		i++;
	}
}

//a cmd will never be empty bc there will always be the pipe token
void	remove_empty_tokens(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->word[0] == '\0')
				erase_token(&token, &cmd_array[i], shell);
			else if (token)
				token = token->next;
		}
		i++;
	}
}

void	parse(t_shell *shell)
{
	char		*no_token_after_redir;

	set_redir_arg_flags(shell->cmd_array);
	no_token_after_redir = NULL;
	set_flag_after_redirection(shell->cmd_array, &no_token_after_redir);
	if (no_token_after_redir)
	{
		err_clear(shell, NOTHING_AFTER_REDIR, no_token_after_redir);
		free(no_token_after_redir);
		return ;
	}
	arg_syntax_processing(shell->cmd_array, shell);
	remove_empty_tokens(shell->cmd_array, shell);
	first_word_is_cmd_flag(shell->cmd_array);
	split_multiple_words_into_tokens(shell);
	remove_quotes(shell->cmd_array, shell);
	create_empty_cmds_list(shell, shell->nb_of_cmds);
	create_argument_list(shell->cmd_array, shell);
	create_heredoc(shell, shell->cmd_array, shell->cmds_list);
}
