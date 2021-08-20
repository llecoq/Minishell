/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/20 17:35:05 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shell_var_to_null(t_shell *shell)
{
	shell->change_directory = 1;
	shell->user_dir = NULL;
	shell->input = NULL;
	shell->envp = NULL;
	shell->env_list = NULL;
	shell->path = NULL;
	shell->cmd_array = NULL;
	global_errno = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	set_shell_var_to_null(&shell);
	if (argc == 1)
	{
		store_environment(&shell, env);
		while (1)
		{
			prompt(&shell);
			tokenize(&shell, shell.input);
			free_set_null((void **)&shell.input);
			if (shell.cmd_array == NULL) //in case of missing closing bracket / empty input
				continue;
			parse(&shell);
			evaluator(&shell, shell.cmds_list, shell.nb_of_cmds);
			//if (shell.cmd_array == NULL) //in case of error that does not need to stop program
			//	continue;
			clear_nonessential_memory(&shell);
		}
	}
	else if (argc > 1 && argv)          // args to be processed
		ft_printf(2, "minishell : too many arguments\n");
	clear_memory(&shell);
	return 0;
}
