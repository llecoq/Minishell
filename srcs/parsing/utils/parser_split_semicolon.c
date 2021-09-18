/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_semicolon.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:03:53 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/18 19:17:30 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fill_command_line(t_shell *shell, char *input, int start, int end)
{
	char	*split_cmd;

	split_cmd = calloc_sh(shell, sizeof(char) * (end - start + 1));
	end--;
	while (end >= start)
	{
		split_cmd[end - start] = input[end];
		end--;
	}
	return (split_cmd);
}

static void	find_command_line(char *input, int *i)
{
	char	closing_quote;

	while (input[*i])
	{
		if (input[*i] == SINGLE_QUOTE || input[*i] == DOUBLE_QUOTE)
		{
			closing_quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != closing_quote)
				(*i)++;
			if (input[*i] == closing_quote)
				(*i)++;
		}
		if (input[*i] && input[*i] == SEMICOLON)
		{
			(*i)++;
			return ;
		}
		if (input[*i]
			&& (input[*i] != SINGLE_QUOTE && input[*i] != DOUBLE_QUOTE))
			(*i)++;
	}
}

t_list	*split_by_semicolons(t_shell *shell, char *input)
{
	t_list	*split_cmds;
	char	*cmd_line;
	int		start;
	int		end;

	end = 0;
	start = 0;
	split_cmds = NULL;
	cmd_line = NULL;
	while (input[start])
	{
		find_command_line(input, &end);
		cmd_line = fill_command_line(shell, input, start, end);
		ft_lstadd_back(&split_cmds, ft_lstnew(cmd_line));
		start = end;
		if (input[end])
			end++;
	}
	return (split_cmds);
}
