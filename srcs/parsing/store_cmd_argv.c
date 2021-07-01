/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmd_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 13:35:57 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/01 16:07:47 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A ZOBER

// size_t	count_words(t_token *cmd_array)
// {
// 	size_t	nb_of_words;

// 	nb_of_words = 0;
// 	while (cmd_array)
// 	{
// 		nb_of_words++;
// 		cmd_array = cmd_array->next;
// 	}
// 	return (nb_of_words);
// }

// size_t	count_cmds(t_token **cmd_array)
// {
// 	size_t	nb_of_commands;

// 	nb_of_commands = 0;
// 	while (cmd_array[nb_of_commands])
// 		nb_of_commands++;
// 	return (nb_of_commands);
// }

// void	store_cmd_words(t_shell *shell, t_token *cmd_array, size_t cmd_number)
// {
// 	size_t	nb_of_words;
// 	size_t	i;

// 	nb_of_words = count_words(cmd_array);
// 	ft_printf(1, "cmd_number = %zu   nb_of_words = %zu\n", cmd_number, nb_of_words);
// 	shell->cmd_argv[cmd_number]
// 		= calloc_sh(shell, sizeof(char *) * (nb_of_words + 1));
// 	i = -1;
// 	while (++i <= nb_of_words)
// 	{
// 		shell->cmd_argv[cmd_number][nb_of_words] = cmd_array->word;
// 		cmd_array = cmd_array->next;
// 	}
// }

// // ATTENTION A FREE  + count_commands existe deja dans le tokenizer
// void	store_cmd_argv(t_shell *shell)
// {
// 	size_t	cmd_number;

// 	cmd_number = count_cmds(shell->cmd_array);
// 	shell->cmd_argv = calloc_sh(shell, sizeof(char *) * (cmd_number + 1));
// 	while (cmd_number >= 0)
// 	{
// 		store_cmd_words(shell, shell->cmd_array[cmd_number], cmd_number);
// 		cmd_number--;
// 	}
// }
