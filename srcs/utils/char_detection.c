/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 10:40:29 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 16:38:05 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! this function does not check wether str is only a redirection and not
// >>xxx per example
int	is_redirection(const char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (TRUNC);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == ';')
		return (SEMICOLON);
	else if (str[i] == '<')
		return (INPUT_REDIR);
	return (0);
}

int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '"')
		return (DOUBLE_QUOTE);
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

//to test words 
int	is_word_char(int c)
{
	if (ft_isalnum(c) || c == UNDERSCORE)
		return (1);
	return (0);
}

int	is_other_spe_char_except_question_mark(char c)
{
	if (c == '!' || (c >= '#' && c <= '&') || (c >= '(' && c <= '/') \
	|| (c >= ':' && c <= '>') || c == '@' || (c >= '[' && c <= '`') \
	|| (c >= '{' && c <= '~'))
		return (1);
	return (0);
}
