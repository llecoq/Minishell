/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:51:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 13:32:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_number(char *word)
{
	if (ft_strncmp(word, "cd\0", 3) == 0)
		return (BUILT_CD);
	else if (ft_strncmp(word, "pwd\0", 4) == 0)
		return (BUILT_PWD);
	else if (ft_strncmp(word, "env\0", 4) == 0)
		return (BUILT_ENV);
	else if (ft_strncmp(word, "echo\0", 5) == 0)
		return (BUILT_ECHO);
	else if (ft_strncmp(word, "exit\0", 5) == 0)
		return (BUILT_EXIT);
	else if (ft_strncmp(word, "unset\0", 6) == 0)
		return (BUILT_UNSET);
	else if (ft_strncmp(word, "export\0", 7) == 0)
		return (BUILT_EXPORT);
	return (0);
}

// fonction non testée
int	search_for_builtins(t_shell *shell, t_token *cmd_array)
{
	int	builtin;

	builtin = builtin_number(cmd_array->word);
	if (builtin)
	{
		if (builtin == BUILT_CD && cd(NULL, shell->cmd_argv, NULL) == 0)
				shell->change_directory = 1;
		else if (builtin == BUILT_PWD)
			pwd(NULL, shell->cmd_argv, NULL);
		else if (builtin == BUILT_EXIT)
			ft_exit(shell, 0);
		else if (builtin == BUILT_ENV)
			env(NULL, shell->cmd_argv, NULL);
		// else if (builtin == BUILT_ECHO)
		// 	echo(NULL, shell->cmd_argv, NULL);
		// else if (builtin == BUILT_EXPORT)
		// 	export(NULL, shell->cmd_argv, NULL);
		// else if (builtin == BUILT_UNSET)
		// 	unset(NULL, shell->cmd_argv, NULL);
		return (1);
	}
	return (0);
}
