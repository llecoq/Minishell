/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/23 12:04:24 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
first token is cmd or only spaces

-----------
Check if after a redirection or pipe there is no next command
bash-3.2$ ls -la | wc >
bash: syntax error near unexpected token `newline'

bash-3.2$ ls -la | wc |
> bash: syntax error: unexpected end of file
-------------

Remove "" ' and instead create flag? for easier printing later ?
*/

void	parse(t_shell *shell)
{
	
}