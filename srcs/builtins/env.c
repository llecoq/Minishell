/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:41:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/28 15:47:18 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_shell *shell, char const **argv)
{
	if (argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);   // bash doesnt act the same
		return (1);										// may have different return value
	}
	print_list(shell->env_list);
	return (0);		// SUCCESS !!!
}
