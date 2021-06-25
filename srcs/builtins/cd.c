/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 09:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/25 11:43:22 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	home_is_set(char **absolute_path)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (0);
	}
	*absolute_path = ft_strdup(home);
	return (1);
}

int	valid_args(char const **argv, char **absolute_path)
{
	if (!argv[1] && home_is_set(absolute_path))
		return (1);
	if (!argv[1])
		return (0);
	if ((ft_strncmp(argv[1], "--\0", 3) == 0
		|| ft_strncmp(argv[1], "~\0", 2) == 0))
	{
		if (home_is_set(absolute_path))
			return (1);
		else
			return (0);
	}
	if (argv[1])
	{
		*absolute_path = ft_strdup(argv[1]);
		return (1);
	}
	return (0);
}

//    Returns 0 if the directory is changed, and if $PWD is set successfully when
//    -P is used; non-zero otherwise.
int	cd(const char *path, char const **argv, char const **envp)
{
	char	*absolute_path;

	absolute_path = NULL;
	(void)path;
	(void)envp;
	if ((argv[1] && *argv[1] == 0)
		|| (argv[1] && ft_strncmp(argv[1], "./\0", 3) == 0))  // dans ce cas, pas de changement)
		return (-1);			// shell->change_dir = 0;
	if (valid_args(argv, &absolute_path))
	{
		if (chdir(absolute_path) == -1)
		{
			// rajouter fd dans notre ft_printf ? Ou alors fake ft_printf qui appelle dprintf huehuehue
			dprintf(2, "Minishell: cd: %s: %s\n", argv[1], strerror(errno));
			return (-1);
		}
	}
	else
		return (-1);
	if (absolute_path)
		free(absolute_path);
	return (0);					// shell->change_dir = 1;
}
