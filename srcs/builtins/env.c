/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:41:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/01 16:07:47 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// when unset and exported again, all the variables already existing in envp
// are coming back to the original position in the list
// We need to print it from the tab, because in the linked list there is still
// elements that are unset and should not be printed

void	print_env(t_shell *shell)
{
	int	i;
	
	i = -1;
	while (shell->envp[++i])
	{
		ft_printf(1, "%d     ", i);  // only for tests, delete afterwards
		ft_putstr_fd((char *)shell->envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
}

int	ft_env(t_shell *shell, char **argv)
{
	(void)shell;
	if (argv[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);   // bash doesnt act the same
		return (1);										// may have different return value
	}
	return (0);		// SUCCESS !!!
}
