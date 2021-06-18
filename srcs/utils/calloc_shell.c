/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:08:02 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/18 16:33:38 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*calloc_sh(t_shell *shell, int size)
{
	unsigned char	*ptr;
	int				i;
	
	i = 0;
	ptr = NULL;
	ptr = malloc(size);
	if (!ptr)
		error(shell, 0);
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}
