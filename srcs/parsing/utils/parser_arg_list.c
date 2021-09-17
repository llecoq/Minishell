/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arg_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 16:49:43 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/17 17:45:46 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---------------------------------------------------------------------------*/
/*------------------- CHAR **ARGV CREATION ----------------------------------*/
/*---------------------------------------------------------------------------*/

/*
si aucune commande dans cmd_array alors clean non essential et retour a prompt
sans msg d'erreur ex : $4 $4

!! a bien checker a chaque cmd_array[i] si error = 1, dans ce cas on ne cree
pas de char **argv

We do not include redirections tokens in char **argv.
**argv just points to the address of the token word in the token structure
*/

static int	arg_count(t_token *token)
{
	int			nb_of_arg;

	nb_of_arg = 0;
	while (token)
	{
		if (token->cmd || token->arg)
			nb_of_arg++;
		token = token->next;
	}
	return (nb_of_arg);
}

static void	link_arg_pointers(t_token *token, char **argv)
{
	t_token		*head;
	int			i;

	head = token;
	while (token)
	{
		if (token->cmd)
		{
			(argv)[0] = token->word;
			break ;
		}
		token = token->next;
	}
	i = 1;
	while (head)
	{
		if (head->arg)
		{
			(argv)[i] = head->word;
			i++;
		}
		head = head->next;
	}
}

// I put the char **argv in the cmd token, the char **argv is ended with a NULL
// char **argv is created for every cmd, even the empty/error ones
void	create_argument_list(t_token **cmd_array, t_shell *shell)
{
	int			i;
	int			argv_nb;
	t_token		*token;
	t_cmd		*cmd;

	i = 0;
	cmd = shell->cmds_list;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		cmd->token_list = cmd_array[i];
		while (token)
		{
			if (token->cmd == 1)
			{
				argv_nb = arg_count(cmd_array[i]);
				cmd->argv = calloc_sh(shell, sizeof(char *) * (argv_nb + 1));
				link_arg_pointers(cmd_array[i], cmd->argv);
				break ;
			}
			token = token->next;
		}
		cmd = cmd->next;
		i++;
	}
}
