/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/23 16:28:59 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(const char *input)
{
	int		i;
	int		nb_of_cmds;
	char	closing_quote;

	i = 0;
	nb_of_cmds = 1;
	while (input[i])
	{
		if (is_redirection(input, i))
		{
			nb_of_cmds++;
			if (is_redirection(input, i) == APPEND)
				i++;
		}
		else if (is_quote(input[i]))
		{
			closing_quote = input[i];
			i++;
			while (input[i] != closing_quote && input[i])
				i++;
			if (!input[i])
				return (NO_CLOSING_QUOTE);
		}
		i++;
	}
	return (nb_of_cmds);
}

//Tokens are separated by space except when in quotes :
// Ici"la lune"la   -> is only one token
static char	*create_word_token(int i, const char *input, t_shell *shell)
{
	int		start;
	char	*token;
	char	closing_quote;
	
	start = i;
	//dprintf(1, "input[start] == %c\n", input[start]);
	while (input[i])
	{	
		if (is_quote(input[i]))
		{
			closing_quote = input[i];
			i++;
			while (input[i] != closing_quote && input[i])
				i++;
		}
		if (input[i] == ' ')
			break;
		i++;
	}
	token = (char *)calloc_sh(shell, sizeof(char) * (i - start + 1));
	ft_strlcpy(token, input + start, i - start + 1);
	return (token);
}

static char	*create_redirection_token(int i, const char *input, t_shell *shell)
{
	char	*token;
	
	token = NULL;
	if (is_redirection(input, i) == PIPE)
	{
		token = calloc_sh(shell, 2);
		token[0] = '|';
	}
	else if (is_redirection(input, i) == APPEND)
	{
		token = calloc_sh(shell, 3);
		token[0] = '>';
		token[1] = '>';
	}
	else if (is_redirection(input, i) == REDIR)
	{
		token = calloc_sh(shell, 2);
		token[0] = '>';
	}
	return (token);	
}

static char	*return_token(int start, const char *input, t_shell *shell)
{
	char	*token;
	
	if (input[start] == '\0')
		return (calloc_sh(shell, 1));
	else if (is_redirection(input, start))
		token = create_redirection_token(start, input, shell);
	else
		token = create_word_token(start, input, shell);
	return (token);
}

static void	split_into_tokens(int nb_of_cmds, const char *input, t_shell *shell)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	shell->cmd_array = calloc_sh(shell, sizeof(t_token) * nb_of_cmds + 1);
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (!input[i] && i != 0)
			break;
		token = return_token(i, input, shell);
		//dprintf(1, "token = %s|\n", token);
		add_token_tail(&shell->cmd_array[j], create_new_token(token, shell));
		i += ft_strlen(token);
		if (is_redirection(return_tail_token(shell->cmd_array[j])->word, 0))
			j++;
		free_set_null((void **)&token);
	}
}

//Adds one extra cmd_array that is set to NULL for easier iterations
void	tokenize(t_shell *shell, const char *input)
{
	int		nb_of_cmds;

	if (input[0] == '\0')
		return ;
	if (finished_by_spaces(input))
		return ;
	nb_of_cmds = count_commands(input);
	if (nb_of_cmds == NO_CLOSING_QUOTE)
	{
		error(shell, NO_CLOSING_QUOTE);
		return ;
	}
	//dprintf(1, "nb of cmds = %d\n", nb_of_cmds);
	split_into_tokens(nb_of_cmds, input, shell);
	
	//print_cmd_array(shell->cmd_array); // A SUPPRIMER
	//dprintf(1, "pointer shell->cmd_array = %p\n", shell->cmd_array);//verify that is null
}
