/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:54:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 18:35:59 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	char	*path;
	
	path = NULL;
	path = getcwd(path, 100);
	while (*path)
		path++;
	while (*path != '/')
		path--;
	path++;
	return (path);
}

void	prompt(t_shell *shell)
{
	char	*line;
	char	*user;
	char	*path;

    user = getenv("USER");
	if (shell)
	{
		path = get_path();
		printf(BOLDMAGENTA " %s: " RESET, user);
		printf(BOLDWHITE "%s " RESET, path);
		line = readline(" ");
		add_history(line);
		free(line);
	}
}