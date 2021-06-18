/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_typeor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 15:25:16 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/18 15:28:00 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_type(t_shell *shell, int error_type)
{
	if (error_type == 0) //syscall errors
		printf("%s\n", strerror(errno));
	// else if (error_type == 1)
	// 	dprintf(1, "");
	// else if (error_type == 2)
	// 	dprintf(1, "");
	// else if (error_type == 3)
	// 	dprintf(1, "");
	// else if (error_type == 4)
	// 	dprintf(1, "");
	// else if (error_type == 5)
	// 	dprintf(1, "");
	// else if (error_type == 6)
	// 	dprintf(1, "");
	clean_memory(d);
	//exit()??
}