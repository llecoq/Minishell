/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:38:58 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 16:40:04 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return -closing_quote to print the error message with corresponding quote
int	count_commands(const char *input)
{
	int		i;
	int		nb_of_cmds;
	char	closing_quote;

	i = 0;
	nb_of_cmds = 1;
	while (input[i])
	{
		if (is_redirection(input, i) == PIPE)
			nb_of_cmds++;
		else if (is_quote(input[i]))
		{
			closing_quote = input[i];
			i++;
			while (input[i] != closing_quote && input[i])
				i++;
			if (!input[i])
				return (-closing_quote);
		}
		i++;
	}
	return (nb_of_cmds);
}
