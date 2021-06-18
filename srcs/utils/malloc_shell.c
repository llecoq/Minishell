/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:08:02 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/18 15:47:10 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc_shell(t_shell *shell, int size)
{
	void	*ptr;
	
	ptr = NULL;
	ptr = malloc(size);
	if (!ptr)
		error(shell, 0);
	return (ptr);
}
