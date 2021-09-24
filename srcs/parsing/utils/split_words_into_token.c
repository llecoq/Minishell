/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_into_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 09:57:27 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 15:44:16 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_first_token(t_token **token, char **splitted_token)
{
	free((*token)->word);
	(*token)->word = *splitted_token;
	(*token)->next = NULL;
}

static void	split_token(t_shell *shell, t_token **token, int i)
{
	char	**splitted_token;
	t_token	*next_token;

	next_token = (*token)->next;
	splitted_token = ft_split((*token)->word, SPACE);
	setup_first_token(token, splitted_token);
	add_tokens_to_list(shell, shell->cmd_array[i], splitted_token);
	return_tail_token(shell->cmd_array[i])->next = next_token;
	free(splitted_token);
}

static int	find_multiple_words(char *word)
{
	int	i;

	i = 0;
	if (*word != SINGLE_QUOTE && *word != DOUBLE_QUOTE)
	{
		while (word[i] && word[i] != SPACE)
			i++;
		if (word[i])
			return (IS_MULTIPLE);
	}
	return (IS_SINGLE);
}

static int	cmd_is_export(t_token *token)
{
	if (token->cmd == 1)
	{
		if (ft_strncmp(token->word, "export", 7) == 0)
			return (1);
	}
	return (0);
}

void	split_multiple_words_into_tokens(t_shell *shell)
{
	t_token	*head;
	int		nb_of_words;
	int		i;

	i = 0;
	while (shell->cmd_array[i])
	{
		head = shell->cmd_array[i];
		while (shell->cmd_array[i])
		{
			if (cmd_is_export(shell->cmd_array[i]))
				break ;
			nb_of_words = find_multiple_words(shell->cmd_array[i]->word);
			if (nb_of_words == IS_MULTIPLE)
				split_token(shell, &shell->cmd_array[i], i);
			shell->cmd_array[i] = shell->cmd_array[i]->next;
		}
		shell->cmd_array[i] = head;
		reset_previous_pointers(head);
		i++;
	}
}
