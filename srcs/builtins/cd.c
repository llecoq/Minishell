/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 09:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/28 15:39:04 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_old_path_to_env(t_shell *shell, char **new_path, char **old_path)
{
	char	*var_name;
	char	*tmp;
	
	var_name = "OLDPWD=";
	tmp = *old_path;
	*old_path = ft_strjoin(var_name, *old_path);
	free(tmp);
	put_env(shell, *old_path);
	free(*old_path);
	if (*new_path)
		free(*new_path);
	shell->change_directory = 1;
}

int	home_is_set(t_shell *shell, char **new_path)
{
	char	*home;

	home = get_env(shell, "HOME"); // attention, on devra chercher directement dans NOTRE env_list
	if (home == NULL)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (0);
	}
	*new_path = home;
	return (1);
}

int	valid_args(t_shell *shell, char const **argv, char **new_path)
{
	if (!argv[1] && home_is_set(shell, new_path))
		return (1);
	if (!argv[1])
		return (0);
	if ((ft_strncmp(argv[1], "--\0", 3) == 0
		|| ft_strncmp(argv[1], "~\0", 2) == 0))
	{
		if (home_is_set(shell, new_path))
			return (1);
		else
			return (0);
	}
	if (argv[1])
	{
		*new_path = ft_strdup(argv[1]);
		return (1);
	}
	return (0);
}

// A TESTER DE NOUVEAU AVEC OLDPWD et leaks
//    Returns 0 if the directory is changed, and if $PWD is set successfully when
//    -P is used; non-zero otherwise.
//	  still have to handle options, what error message should we print ?
int	cd(t_shell *shell, char const **argv)
{
	char	*new_path;
	char	*old_path;

	new_path = NULL;
	old_path = getcwd(NULL, 0);
	if ((argv[1] && *argv[1] == 0)
		|| (argv[1] && ft_strncmp(argv[1], "./\0", 3) == 0))  // dans ce cas, pas de changement)
		return (-1);			// shell->change_dir = 0;
	if (valid_args(shell, argv, &new_path))
	{
		if (chdir(new_path) == -1)
		{
			free(new_path);
			free(old_path);
			dprintf(2, "Minishell: cd: %s: %s\n", argv[1], strerror(errno));
			return (-1);
		}
	}
	else
		return (-1);
	add_old_path_to_env(shell, &new_path, &old_path);
	return (0);
}
