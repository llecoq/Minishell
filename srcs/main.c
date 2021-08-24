/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/24 13:53:01 by llecoq           ###   ########.fr       */
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
	exit_status = 0;
}

// LEAKS ?
void	execute_minishell_script(t_shell *shell, char **argv, char **envp)
{
	int		fd;
	int		ret;

	fd = open(argv[1], O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &shell->input);
		if (ret <= 0)
			ft_exit(shell, NULL);
		store_environment(shell, envp);
		tokenize(shell, shell->input);
		parse(shell);
		evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
		clear_nonessential_memory(shell);
	}
	clear_memory(shell);
}

void	execute_minishell_from_string(t_shell *shell, char *arg, char **envp)
{
	shell->input = arg;
	store_environment(shell, envp);
	tokenize(shell, shell->input);
	parse(shell);
	evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
	ft_exit(shell, NULL);
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
	else if (argc == 2 && ft_strncmp(argv[1], "./", 2) == 0)          // args to be processed
		execute_minishell_script(&shell, argv, envp);
	else if (argc >= 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		execute_minishell_from_string(&shell, argv[2], envp);
	else
		ft_printf(2, "minishell: Wrong use. Try again !\n");
	clear_memory(&shell);
	return (exit_status);
}
