/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:42:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 10:14:36 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// when unset and exported again, all the variables already existing in envp
// are coming back to the original position in the list.
// instead of deleting the content of the list, maybe just put a flag in it
// and store it only if the flag is positive (we can keep it in the linked list
// but not in the tab that we'll send to execve)

int	unset(t_shell *shell, char **argv)
{
	
}