/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_for_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 11:51:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/28 14:33:27 by abonnel          ###   ########.fr       */
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
//enlever la partie qui lance la fonction direct, et en valeur de retour pointeur
//sur fonction correspondant
// fonction non testée, fd à rajouter pour gérer redirections 
int	search_for_builtins(t_shell *shell, t_token *cmd_array)
{
	int	builtin;

	builtin = builtin_number(cmd_array->word);
	if (builtin)
	{
		//doit ajouter $OLDPWD dans env_tab
		if (builtin == BUILT_CD && cd(shell, NULL, shell->cmd_argv, NULL) == 0)
			store_environment_tab(shell, shell->env_list, ft_lstsize(shell->env_list));
		else if (builtin == BUILT_PWD)
			pwd(shell, NULL, shell->cmd_argv, NULL);
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
