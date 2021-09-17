/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:55:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/17 17:46:18 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interpret_and_write_into_fd(int fd, char *input, t_shell *shell)
{
	replace_token_with_var(&input, shell);
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

static void	heredoc_prompt(t_shell *shell, char *limiter, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input)
		{
			if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
			{
				free(input);
				return ;
			}
			interpret_and_write_into_fd(fd, input, shell);
		}
		else if (input == NULL)
			return ;
	}
}

static void	search_for_heredoc(t_token *token_list, t_cmd *cmd, char **limiter)
{
	t_token	*token;

	token = token_list;
	while (token)
	{
		if (token->redir == HEREDOC)
		{
			cmd->redir.from_heredoc = EXISTENT;
			(*limiter) = token->next->word;
			return ;
		}
		token = token->next;
	}
	return ;
}

void	create_heredoc(t_shell *shell, t_token **cmd_array, t_cmd *cmds_list)
{
	char	*limiter;
	int		pipefd[2];
	int		i;
	t_cmd	*cmd;

	cmd = cmds_list;
	i = 0;
	while (cmd_array[i] != NULL)
	{
		search_for_heredoc(cmd_array[i], cmd, &limiter);
		if (cmd->redir.from_heredoc == EXISTENT)
		{
			if (pipe(pipefd) == FAILED)
				error_quit(shell, SYSCALL_ERROR, NULL);
			heredoc_prompt(shell, limiter, pipefd[1]);
			close(pipefd[1]);
			cmd->redir.from_heredoc = pipefd[0];
		}
		cmd = cmd->next;
		i++;
	}
}
