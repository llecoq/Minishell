/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_trim_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 12:21:58 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/12 16:41:14 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Quand token = "" -> deviendra '\0', c'est ce qu'on veux car quand on envoi
//"\0" dans le char argv de echo, il imprime d'emblee un espace a la place
static void	remove_quotes_char(char *word, t_shell *shell)
{
	int			i;
	char		closing_quote;

	i = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
		{
			closing_quote = word[i];
			ft_memmove(word + i, word + i + 1, ft_strlen(word + i));
			while (word[i] && word[i] != closing_quote)
				i++;
			if (word[i] == closing_quote)
			{
				ft_memmove(word + i, word + i + 1, ft_strlen(word + i));
				i--;
			}
		}
		i++;
	}
	(void)shell;
}

void	remove_quotes(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			remove_quotes_char(token->word, shell);
			token = token->next;
		}
		i++;
	}
}
