/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/21 18:55:27 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" //switch back to minishell.h only

static int	count_commands(const char *input)
{
	int		i;
	int		nb_of_cmds;

	i = 0;
	nb_of_cmds = 1;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>')
		{
			nb_of_cmds++;
			if (input[i] == '>' && input[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (nb_of_cmds);
}

int	count_token_len(int i, const char *input)
{
	int		start;
	
	start = i;
	//si on debute sur " ou '
	if ((input[i] == '"' || input[i] == 39) && i == start)
	{
		while (input[i] != '"' && input[i] != 39 && input[i])
			i++;
		if (!input[i])
			return (-1); //error, didn't find closing " or '
		else
			return (i - start);
	}
	while (input[i])
	{
		//!! a corriger, si on commence sur un des char stoppants 
		//alors on ne va pas avancer ++ ! au cas particulier >>
		if (input[i] == ' ' || input[i] == '>' || input[i] == '|' || input[i] == '"' || input[i] == 39) //create enum for those chars
			break;
		i++;
	}
	return (i - start);
}


static void	split_into_tokens(t_token **cmd_array, const char *input, t_shell *shell)
{
	int		i;
	int		j;
	int		token_len;

	i = 0;
	j = 0;
	while (input[i])
	{
		//SEULE ERREUR POSSIBLE : ne pas trouver le " ou ' suivant
		//dans ce cas tout free y compris input
		//renvoyer -1 a token_len
		//token_len = count_char(start = i) between ' ', " and ', if > >> ou | rester sur ce char
		token_len = count_token_len(i, input);
		// if (token_len == -1)
		// 	error();
		//add_token_tail 
		//copy string(start = i, end = token_len + i)
		//i += token_len
		//if input[i] = > ou >> ou | alors j++;
	}
}

t_token	**tokenize(t_shell *shell, const char *input)
{
	int		nb_of_cmds;
	t_token **cmd_array;

	if (input[0] == '\0')//if no input we receive a \0, not a \n
		return NULL;
	cmd_array = NULL;
	nb_of_cmds = count_commands(input);
	// dprintf(1, "nb of cmds = %d\n", nb_of_cmds);
	//cmd + 1 so that last one is set to NULL
	cmd_array = calloc_sh(shell, sizeof(t_token) * nb_of_cmds + 1);
	//dprintf(1, "sizeof(token *) = %d sizeof(token) = %d\n", sizeof(t_token *), sizeof(t_token));
	//split_into_tokens(cmd_array, *input, shell);
	
	//Free in parent function bc input is const here
	//&& only one free for null input or else
	//free_set_null(input); 
	return (cmd_array);
}