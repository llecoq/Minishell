/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/30 20:42:25 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
-----------------------------------------------------------------------------------------
→ **Verify if each CMD token is** **true** : echo / cd / pwd/ export / unset/ env / exit,
otherwise look through paths and **save path in node**. 
/!\ "echo" works so we need to do preprocessing before

Else : free and "zsh: command not found: lsls" 

----------------------------------------------------------------------------------------
→ CREATE char **argv : nb of arg = cmd + nb of flag arg

in case command is only spaces, in bash it IS a command so I did create a cmd_array for it

Before putting in argv, trim out the ' and " and for " replace the $env var
cd "Documents"/42cursus fonctionne ! -> cherche cd Documents/42cursus

We only put cmd and args flags in char **argv
---------------------------------------------------------------------------------------
*/

static void	initialize_flags_values(t_token **cmd_array)
{
	int			i;
	t_token		*cpy;

	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		while (cpy)
		{
			cpy->cmd = -1;
			cpy->arg = -1;
			cpy->redir = -1;
			cpy = cpy->next;
		}
		i++;
	}
}

static void	turn_on_flag(int flag, t_token *cpy)
{
	if (flag == CMD)
		cpy->cmd = 1;
	else
		cpy->cmd = 0;
	if (flag == ARG)
		cpy->arg = 1;
	else
		cpy->arg = 0;
	if (flag == REDIR)
		cpy->redir = 1;
	else
		cpy->redir = 0;
}

static int	after_redir(t_token **cpy, t_token *next_cmd)
{
	t_token		*next_token;
	
	next_token = (*cpy)->next;
	if (is_redirection((*cpy)->word, 0) == PIPE && next_cmd == NULL)
		return (NOTHING_AFTER_REDIR);
	else if (is_redirection((*cpy)->word, 0) != PIPE)
	{
		if (next_token == NULL)
			return (NOTHING_AFTER_REDIR);
		*cpy = (*cpy)->next;
		turn_on_flag(REDIR, *cpy);
	}
	return (1);
}

static int	set_flags(t_token **cmd_array)
{
	int			i;
	t_token		*cpy;
	
	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		turn_on_flag(CMD, cpy);
		cpy = cpy->next;
		while (cpy)
		{
			if (is_redirection(cpy->word, 0))
			{
				turn_on_flag(REDIR, cpy); // A CHANGER
				if (after_redir(&cpy, cmd_array[i + 1]) == NOTHING_AFTER_REDIR)
					return (NOTHING_AFTER_REDIR);			
			}
			else
				turn_on_flag(ARG, cpy);
			cpy = cpy->next;
		}
		i++;
	}
	return (1);
}

/* 
We first initialize flags values by default to -1 bc it will allow us to make sure
they have all been properly set
Then we set each to 1 or 0
*/
void	parse(t_shell *shell)
{
	initialize_flags_values(shell->cmd_array);
	//if (shell->cmd_array[0]->cmd)
	//	dprintf(1, "flag cmd = %d\n", shell->cmd_array[0]->cmd);
	// dprintf(1, "flag arg = %d\n", shell->cmd_array[0]->arg);
	// dprintf(1, "flag redir = %d\n", shell->cmd_array[0]->redir);
	if (set_flags(shell->cmd_array) == NOTHING_AFTER_REDIR)
	{
		error(shell, NOTHING_AFTER_REDIR);
		return ;
	}
	//dprintf(1, "END OF PARSE()\n");
}