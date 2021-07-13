/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_into_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:48:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/13 20:43:43 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum	e_word
{
	IS_SINGLE,
	IS_MULTIPLE,
	DOUBLE_QUOTE = 34,
	QUOTE = 39,
	// SPACE = 32,
};

static void	add_to_list(t_shell *shell, t_token *head, char	**word)
{
	t_token *new_token;
	int		i;
	
	i = 0;
	while (word[i])
	{
		new_token = create_new_token(word[i], shell);
		turn_on_flag(ARG, new_token);
		add_token_tail(&head, new_token);
		i++;
	}
}

// attention a free l'ancien maillon
void	split_token(t_shell *shell, t_token **head, t_token *token)
{
	t_token	*next_token;
	char	**splitted_words;

	next_token = token->next;
	splitted_words = ft_split(token->word, SPACE);
	if (token->previous)
		token->previous->next = NULL;
	add_to_list(shell, *head, splitted_words);
	return_tail_token(*head)->next = next_token;
	free_split(splitted_words);
}

int	find_multiple_words(char *word)
{
	int	i;

	i = 0;
	if (*word != QUOTE && *word != DOUBLE_QUOTE)
	{
		while (word[i] && word[i] != SPACE)
			i++;
		if (word[i])
			return (IS_MULTIPLE);
	}
	return (IS_SINGLE);
}

void	split_multiple_words_into_token(t_shell *shell, t_token ***cmd_array)
{
	t_token	*head;
	int		i;
	int		token_word;

	head = NULL;
	token_word = 0;
	i = 0;
	while ((*cmd_array)[i])
	{
		head = *cmd_array[i];
		while (*cmd_array[i])
		{
			token_word = find_multiple_words((*cmd_array[i])->word);
			if (token_word == IS_MULTIPLE)
				split_token(shell, &head, *cmd_array[i]);
			*cmd_array[i] = (*cmd_array[i])->next;
		}
		*cmd_array[i] = head;
		i++;
	}
}	
