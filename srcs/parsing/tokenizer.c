/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/18 14:43:51 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_token	**tokenize(t_shell *shell, char **input)
{
	int		nb_of_cmds;

	if (*input[0] == '\0')//if no input we receive a \0, no a \n
	{
		free_set_null((void **)input);
		return;
	}
	nb_of_cmds = count_commands(*input);
	dprintf(1, "nb of cmds = %d\n", nb_of_cmds);
	
	(void)shell;
}
