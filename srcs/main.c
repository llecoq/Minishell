/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 13:28:36 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_environment(t_shell *shell, char **env)
{
	while (*env)
	{
		ft_lstadd_back(&shell->path, ft_lstnew(*env));
		env++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (argc == 1 && argv)                             // besoin de argv ?
	{
		store_environment(&shell, env);
		prompt(&shell);
	}
	else
		dprintf(1, "minishell : too many arguments\n");    // à changer
	return 0;
}
