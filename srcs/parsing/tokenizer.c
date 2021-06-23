/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/22 15:00:24 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" //switch back to minishell.h only

static int	count_commands(const char *input, t_shell *shell)
{
	int		i;
	int		nb_of_cmds;
	char	closing_quote;

	i = 0;
	nb_of_cmds = 1;
	while (input[i])
	{
		if (is_redirection(input, i)) //input[i] == '|' || input[i] == '>')
		{
			nb_of_cmds++;
			if (is_redirection(input, i) == APPEND)
				i++;
		}
		else if (is_quote(input[i])) //if quote looks for closing one
		{
			closing_quote = input[i];
			i++;
			while (input[i] != closing_quote && input[i])
				i++;
			if (!input[i])
				error(shell, 1);
		}
		i++;
	}
	return (nb_of_cmds);
}

//We include the space after the closing quote except if it is the last token
//We do that bc behaviour will differ : if there is no space between two quoted
//tokens then there will not be space between them when printed
static char	*create_quoted_token(int i, const char *input, t_shell *shell)
{
	int		start;
	char	closing_quote;
	char	*token;

	start = i;
	closing_quote = input[i];
	i++;
	while (input[i] != closing_quote && input[i])
		i++;
	//if !input[i] --> ne devrait pas arriver
	if (!(finished_by_spaces(input + i + 1)) && input[i + 1] == ' ')
		i++;
	token = (char *)calloc_sh(shell, sizeof(char) * (i - start + 2));
	ft_strlcpy(token, input + start, i - start + 2);
	return (token);
}

static char	*create_word_token(int i, const char *input, t_shell *shell)
{
	int		start;
	char	*token;
	
	start = i;
	// dprintf(1, "input[start] == %c\n", input[start]);
	while (!(is_quote(input[i]) || is_redirection(input, i) || input[i] == ' ') && input[i])
		i++;
	token = (char *)calloc_sh(shell, sizeof(char) * (i - start + 1));
	ft_strlcpy(token, input + start, i - start + 1);
	return (token);
}

// static char	*create_redirection_token(int i, const char *input, t_shell *shell)
// {
// 	char	*token;
	
// 	if (is_redirection(input, i) == PIPE)
// 	{
// 		token = calloc_sh(shell, 2);
// 		token[0] = '|';
// 	}
// 	else if (is_redirection(input, i) == APPEND)
// 	{
// 		token = calloc_sh(shell, 3);
// 		token[0] = '>';
// 		token[1] = '>';
// 	}
// 	else if (is_redirection(input, i) == REDIR)
// 	{
// 		token = calloc_sh(shell, 2);
// 		token[0] = '>';
// 	}
// 	return (token);	
// }

static char	*return_token(int start, const char *input, t_shell *shell)
{
	char	*token;
	
	if (input[start] == '\0')
		return (calloc_sh(shell, 1));
	else if (is_quote(input[start]))
		token = create_quoted_token(start, input, shell);
	// else if (is_redirection(input, start))
	// 	token = create_redirection_token(start, input, shell);
	else
		token = create_word_token(start, input, shell);
	return (token);
}

static void	split_into_tokens(t_token **cmd_array, const char *input, t_shell *shell)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		token = return_token(i, input, shell);
		dprintf(1, "token = %s|\n", token);
		//add_token_tail(cmd_array[], create_new_token(token, shell))
		i += ft_strlen(token);//verifier qu'on arrive bien juste APRES token
		//if is_redirection(token_tail->word[0]), j++;
		free_set_null((void **)&token);
	}
	(void)cmd_array;
	(void)shell;
}

t_token	**tokenize(t_shell *shell, const char *input)
{
	int		nb_of_cmds;
	t_token **cmd_array;

	if (input[0] == '\0')//if no input we receive a \0, not a \n
		return NULL;
	cmd_array = NULL;
	nb_of_cmds = count_commands(input, shell);
	dprintf(1, "nb of cmds = %d\n", nb_of_cmds);
	//cmd + 1 so that last one is set to NULL
	cmd_array = calloc_sh(shell, sizeof(t_token) * nb_of_cmds + 1);
	//dprintf(1, "sizeof(token *) = %d sizeof(token) = %d\n", sizeof(t_token *), sizeof(t_token));
	
	split_into_tokens(cmd_array, input, shell);
	
	//Free_set_null(input) in parent function bc input is const here
	//&& only one free for null input or else
	return (cmd_array);
}
