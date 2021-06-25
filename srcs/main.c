/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 12:56:30 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shell_var_to_null(t_shell *shell)
{
	shell->user_dir = NULL;
	shell->change_directory = 1;
	shell->input = NULL;
	shell->envp = NULL;
	shell->env_list = NULL;
	shell->path = NULL;
	shell->cmd_array = NULL;
}

int	main(int argc, const char **argv, const char **env)
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
			free_cmd_array(shell.cmd_array);//a enlever
			free(shell.cmd_array);//a enlever
			shell.cmd_array = NULL; //a enlever
			//parser();
		}
	}
	else if (argc > 1 && argv)          // args to be processed
		dprintf(2, "minishell : too many arguments\n");
	clear_memory(&shell);
	return 0;
}
