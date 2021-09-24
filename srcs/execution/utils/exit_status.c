/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:51:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/24 15:42:57 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wexitstatus(int status)
{
	int	w_int;

	w_int = (*(int *)&(status));
	return (((w_int >> 8) & 0x000000ff));
}

int	last_child_status(pid_t last_child_pid)
{
	int	child_status;

	waitpid(last_child_pid, &child_status, 0);
	child_status = wexitstatus(child_status);
	return (child_status);
}
