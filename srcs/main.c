/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/22 14:30:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (argc == 1)
	{
		store_environment(&shell, env);
		while (1)
			prompt(&shell);
	}
	else if (argc > 1 && argv)          // args to be processed
		dprintf(1, "minishell : too many arguments\n");
	clear_memory(&shell);
	return 0;
}
