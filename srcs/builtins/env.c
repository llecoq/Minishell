/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:41:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/24 15:19:52 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(const char *path, char const **argv, char const **envp)
{
	(void)path;
	(void)argv;
	if (argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);   // bash doesnt act the same
		return (1);										// may have different return value
	}
	while (*envp)
	{
		ft_putstr_fd((char *)*envp++, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);		// SUCCESS !!!
}
