/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 20:35:25 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shell_var_to_null(t_shell *shell)
{
	shell->change_directory = 1;
	shell->exit_code = 0;
	shell->user_dir = NULL;
	shell->input = NULL;
	shell->envp = NULL;
	shell->env_list = NULL;
	shell->path = NULL;
	shell->cmd_array = NULL;
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;

// 	(void)argc;
// 	(void)argv;
// 	set_shell_var_to_null(&shell);
// 	if (argc == 1)
// 	{
// 		store_environment(&shell, env);
// 		while (1)
// 		{
// 			prompt(&shell);
// 			tokenize(&shell, shell.input);
// 			free_set_null((void **)&shell.input);
// 			if (shell.cmd_array == NULL) //in case of missing closing bracket / empty input
// 				continue;
// 			free_cmd_array(shell.cmd_array);//a enlever
// 			free(shell.cmd_array);//a enlever
// 			shell.cmd_array = NULL; //a enlever
// 			//parser();
// 		}
// 	}
// 	else if (argc > 1 && argv)          // args to be processed
// 		dprintf(2, "minishell : too many arguments\n");
// 	clear_memory(&shell);
// 	return 0;
// }

// char	*search_for_path(const char *prog_name, t_list *path_list)
// {
// 	char	*full_path;
// 	char	*tmp;
// 	int		fd;

// 	tmp = "/";
// 	tmp = ft_strjoin(tmp, prog_name);
// 	while (path_list)
// 	{
// 		full_path = ft_strjoin(path_list->content, tmp);
// 		fd = open(full_path, O_RDONLY);
// 			dprintf(1, "full_path = %s  fd = %d\n",full_path, fd);
// 		if (fd > 0)
// 		{
// 			close(fd);
// 			free(tmp);
// 			return (full_path);
// 		}
// 		free(full_path);
// 		path_list = path_list->next;
// 	}
// 	return (NULL);
// }

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
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
			if (shell.cmd_array == NULL) //in case of error that does not need to stop program
				continue;
			clear_nonessential_memory(&shell);
		}
	}
	else if (argc > 1 && argv)          // args to be processed
		dprintf(2, "minishell : too many arguments\n");
	clear_memory(&shell);
	return 0;
}
