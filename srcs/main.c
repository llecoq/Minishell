/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 16:42:14 by llecoq           ###   ########.fr       */
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
	shell->export_list = NULL;
	shell->path = NULL;
	shell->cmd_array = NULL;
	shell->cmds_list = NULL;
	shell->split_cmds_by_semicolons = NULL;
	shell->execute_minishell_from_str = FALSE;
	shell->flush_stdin = FALSE;
	shell->child_process = FALSE;
	g_exit_status = 0;
}

void	execute_minishell_from_string(t_shell *shell, char *arg, char **envp)
{
	shell->input = arg;
	shell->execute_minishell_from_str = TRUE;
	store_environment(shell, envp);
	process_input(shell, STRING);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	set_shell_var_to_null(&shell);
	if (argc == 1)
	{
		store_environment(&shell, envp);
		while (1)
		{
			prompt(&shell);
			process_input(&shell, PROMPT);
		}
	}
	else if (argc >= 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		execute_minishell_from_string(&shell, argv[2], envp);
	else
	{
		ft_printf(2, "minishell: Wrong use. Try again !\n");
		g_exit_status = 42;
	}
	clear_memory(&shell);
	return (g_exit_status);
}
