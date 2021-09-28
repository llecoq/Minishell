/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/28 16:10:32 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_word_token(int i, const char *input, t_shell *shell)
{
	int		start;
	char	*token;
	char	closing_quote;

	start = i;
	while (input[i])
	{	
		if (is_quote(input[i]))
		{
			closing_quote = input[i];
			i++;
			while (input[i] != closing_quote && input[i])
				i++;
		}
		if (input[i] == ' ' || is_redirection(input, i))
			break ;
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
	token = calloc_sh(shell, 3);
	if (is_redirection(input, i) == PIPE)
		ft_strlcpy(token, "|", 2);
	if (is_redirection(input, i) == SEMICOLON)
		ft_strlcpy(token, ";", 2);
	else if (is_redirection(input, i) == TRUNC)
		ft_strlcpy(token, ">", 2);
	else if (is_redirection(input, i) == APPEND)
		ft_strlcpy(token, ">>", 3);
	else if (is_redirection(input, i) == INPUT_REDIR)
		ft_strlcpy(token, "<", 2);
	else if (is_redirection(input, i) == HEREDOC)
		ft_strlcpy(token, "<<", 3);
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
	int		redir_type;
	char	*token;

	i = 0;
	j = 0;
	shell->cmd_array = calloc_sh(shell, sizeof(t_token) * nb_of_cmds + 1);
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (!input[i] && i != 0)
			break ;
		token = return_token(i, input, shell);
		add_token_tail(&shell->cmd_array[j], create_new_token(token, shell));
		i += ft_strlen(token);
		redir_type = \
		is_redirection(return_tail_token(shell->cmd_array[j])->word, 0);
		if (redir_type == PIPE)
			j++;
		free_set_null((void **)&token);
	}
}

//Cmd_array is finished by NULL for easier iterations
//One commands end at \n or at a pipe
//Tokens are either :
//	- redirection > >> < << | that does not need to be separated from other
//	letters by any space to be recognized as such
//	- words that are separated by space, though spaces do not split a word if
//	surrounded by "" or ''  ex : ici"la lune"rouge   == one token only
void	tokenize(t_shell *shell, const char *input)
{
	int		nb_of_cmds;

	if (input[0] == '\0')
		return ;
	if (input[0] == '|' || input[0] == ';')
	{
		((char *)input)[1] = '\0';
		err_clear(shell, NOTHING_BEFORE_REDIR, (char *)input);
		return ;
	}
	if (finished_by_spaces(input))
		return ;
	nb_of_cmds = count_commands(input);
	shell->nb_of_cmds = nb_of_cmds;
	if (nb_of_cmds == -SINGLE_QUOTE || nb_of_cmds == -DOUBLE_QUOTE)
	{
		err_clear(shell, nb_of_cmds, NULL);
		return ;
	}
	split_into_tokens(nb_of_cmds, input, shell);
}
