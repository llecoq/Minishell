/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:40:29 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/28 15:19:42 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(const char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (REDIR);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '<')
		return (INREDIR);
	return (0);
}

int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '"')
		return (DBLE_QUOTE);
	return (0);
}

int	finished_by_spaces(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' && str[i])
		i++;
	if (!str[i])
		return (1);
	return (0);
}