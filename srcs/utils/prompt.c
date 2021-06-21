/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:54:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/21 18:50:40 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path(char **directory, char *path)
{
	while (*path)
		path++;
	while (*path != '/')
		path--;
	path++;
	*directory = path;
}

void	print_user_dir(void)
{
	char	*user;
	char	*directory;
	char	*path;

	path = NULL;
	user = getenv("USER");
	path = getcwd(NULL, 0);
	get_path(&directory, path);
	printf(BOLDMAGENTA " %s: " RESET, user);
	printf(BOLDWHITE "%s " RESET, directory);
	free(path);
}

void	prompt(t_shell *shell)
{
    	print_user_dir();
		shell->input = readline("");
		add_history(shell->input);
		free(shell->input);
	// gerer l'history pour ne pas perdre le user et path
}
