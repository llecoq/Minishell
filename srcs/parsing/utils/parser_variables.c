/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:50:37 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:37:28 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*--------------------------PROCESS_VARIABLES() -----------------------------*/	
/*
Takes a token and returns a NEW string that is the token with expanded var

We must restart at i + length of var value bc otherwise it will interpret 
things it should not so we send an int ptr to insert_var_in_str()
Variables that reference other var inside of themselves are already
processed at the export cmd stage so appear already fully expanded in env. 

In the case below, it shows what would happen if we would restart at the 
position were $ used to be instead of i + length of var value,
it would enter "$USER" and would interpret USER whereas it should not
as it was originaly defined as a string literal and should remain so

bash-3.2$ export NEWW='HEHE"$USER"bonjour'
bash-3.2$ echo "bonjour $NEWW et ensuite"
bonjour HEHE"$USER"bonjour et ensuite
bash-3.2$ env | grep "NEWW"
NEWW=HEHE"$USER"bonjour
*/
/*---------------------------------------------------------------------------*/

static void	interpret_string(t_shell *shell, char **tk_cpy, int *i)
{
	(*i)++;
	while ((*tk_cpy)[*i] != DOUBLE_QUOTE && (*tk_cpy)[*i])
	{
		if ((*tk_cpy)[*i] == '$' && (*tk_cpy)[*i + 1])
			*i += insert_var_in_str(tk_cpy, *i, shell);
		else
			(*i)++;
	}
	if ((*tk_cpy)[*i])
		(*i)++;
}

static void	do_not_interpret_string(char *tk_cpy, int *i)
{
	(*i)++;
	while (tk_cpy[*i] != SINGLE_QUOTE && tk_cpy[*i])
		(*i)++;
	if (tk_cpy[*i])
		(*i)++;
}

char	*process_variables(char *tk_cpy, t_shell *shell)
{
	int			i;

	if (process_tilde(shell, &i, &tk_cpy) == TRUE)
		return (tk_cpy);
	i = 0;
	while (tk_cpy[i])
	{
		if (dollar_sign_followed_by_quote(tk_cpy, i))
			ft_memmove(tk_cpy + i, tk_cpy + i + 1, strlen(tk_cpy + i));
		else if (tk_cpy[i] == '$' && tk_cpy[i + 1])
			i += insert_var_in_str(&tk_cpy, i, shell);
		else if (tk_cpy[i] == DOUBLE_QUOTE)
			interpret_string(shell, &tk_cpy, &i);
		else if (tk_cpy[i] == SINGLE_QUOTE)
			do_not_interpret_string(tk_cpy, &i);
		else if (tk_cpy[i])
			i++;
	}
	return (tk_cpy);
}

void	replace_token_with_var(char **token, t_shell *shell)
{
	char		*tk_cpy;

	tk_cpy = ft_strdup(*token);
	tk_cpy = process_variables(tk_cpy, shell);
	free_set_null((void **)token);
	*token = tk_cpy;
}

void	arg_syntax_processing(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{
			if (token->redir == 0)
				replace_token_with_var(&token->word, shell);
			token = token->next;
		}
		i++;
	}
}
