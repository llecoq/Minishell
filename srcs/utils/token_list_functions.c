/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:28:56 by abonnel           #+#    #+#             */
/*   Updated: 2021/08/20 19:11:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_previous_pointers(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (head)
	{
		if (head->next)
			head->next->previous = head;
		head = head->next;
	}
	head = tmp;
}

t_token	*return_tail_token(t_token *token_lst)
{
	if (token_lst)
		while (token_lst->next)
			token_lst = token_lst->next;
	return (token_lst);
}

void	add_token_tail(t_token **head, t_token *new_token)
{
	t_token	*last_token;
	
	last_token = NULL;
	if (*head)
	{
		last_token = return_tail_token(*head);
		last_token->next = new_token;
		new_token->previous = last_token;
	}
	else
		*head = new_token;
}

t_token	*create_new_token(char *token, t_shell *shell)
{
	t_token			*new_token;
	
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!(new_token))
		error_quit(shell, SYSCALL_ERROR, NULL);
	new_token->word = ft_strdup(token);
	if (!(new_token->word))
	 	error_quit(shell, SYSCALL_ERROR, NULL);
	new_token->next = NULL;
	new_token->previous = NULL;
	return (new_token);
}

char	*find_redir_type(int flag)
{
	char	*redir_type;

	redir_type = NULL;
	if (flag == PIPE)
		redir_type = "PIPE";
	else if (flag == TRUNC)
		redir_type = "TRUNC";
	else if (flag == APPEND)
		redir_type = "APPEND";
	else if (flag == INPUT_REDIR)
		redir_type = "INPUT_REDIR";
	else if (flag == HEREDOC)
		redir_type = "HEREDOC";
	else if (flag == IS_FILE)
		redir_type = "IS_FILE";
	else if (flag == STOP_VALUE)
		redir_type = "STOP_VALUE";
	return (redir_type);
}

void	print_cmd_array(t_token **cmd_array, int flags)
{
	int				i;
	int				x;
	char			*redir_type;
	t_token			*cpy;

	i = 0;
	ft_printf(1, "===== Print cmd array =====\n");
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		x = 0;
		if (cpy->error)
			ft_printf(1, "\033[1m\033[31m");
		ft_printf(1, "%d\n", i);
		while (cpy)
		{
			ft_printf(1, "cmd[%d], ", i);
			if (flags == 1)
			{
				if (cpy->cmd)
					ft_printf(1, "flag : CMD, ");
				if (cpy->arg)
					ft_printf(1, "flag : ARG, ");
				if (cpy->redir)
				{
					redir_type = find_redir_type(cpy->redir);
					ft_printf(1, "flag : %s, ", redir_type);
				}
			}
			ft_printf(1, "token n*%d = |%s|\n", x, cpy->word);
			cpy = cpy->next;
			x++;
		}
		if (cmd_array[i]->error)
			ft_printf(1, "\033[0m");
		i++;
	}
	ft_printf(1, "====^ Print cmd array ^====\n");
}

static void	print_current_argv(t_cmd *cmd)
{
	int				i;

	i = 0;
	while (cmd->argv[i])
	{
		ft_printf(1, "%s, ", cmd->argv[i]);
		i++;
	}
	ft_printf(1, "NULL");
	ft_printf(1, "\n");
}

void	print_argv(t_cmd *cmds_list)
{
	int				i;
	t_cmd			*cmd;

	i = 0;
	cmd = cmds_list;
	while (cmd)
	{
		ft_printf(1, "COMMAND #%d\n", i);
		print_current_argv(cmd);
		i++;
		cmd = cmd->next;
	}
}

// static void	print_current_argv(t_token *cmd)
// {
// 	int				i;

// 	i = 0;
// 	while (cmd->argv[i])
// 	{
// 		ft_printf(1, "%s, ", cmd->argv[i]);
// 		i++;
// 	}
// 	ft_printf(1, "NULL");
// 	ft_printf(1, "\n");
// }

// void	print_argv(t_token **cmd_array)
// {
// 	int				i;
// 	t_token			*token;

// 	i = 0;
// 	while (cmd_array[i])
// 	{
// 		token = cmd_array[i];
// 		while (token)
// 		{
// 			if (token->cmd == 1)
// 			{
// 				ft_printf(1, "COMMAND #%d\n", i);
// 				print_current_argv(token);
// 			}
// 			token = token->next;
// 		}
// 		i++;
// 	}
// }

void	erase_token(t_token **token, t_token **head, t_shell *shell)
{
	t_token 		*prev;
	t_token			*next;

	prev = (*token)->previous;
	next = (*token)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->previous = prev;
	free_set_null((void **)token);
	(*token) = next;
	if (prev == NULL)
		(*head) = (*token);
	(void)shell;
}

void	erase_cmd(t_token *cmd)
{
	t_token		*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		free_set_null((void **)&tmp->word);
		free_set_null((void **)&tmp);
	}
}
