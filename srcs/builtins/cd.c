/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 09:29:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 13:39:25 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_path_to_env(t_shell *shell, char **new_path)
{
	char	*tmp;

	free(*new_path);
	*new_path = getcwd(NULL, 0);
	tmp = *new_path;
	*new_path = ft_strjoin("PWD=", *new_path);
	free(tmp);
	put_env(shell, *new_path);
	free(*new_path);
	shell->change_directory = 1;
}

void	add_old_path_to_env(t_shell *shell, char **old_path)
{
	char	*tmp;

	tmp = *old_path;
	*old_path = ft_strjoin("OLDPWD=", *old_path);
	free(tmp);
	put_env(shell, *old_path);
	free(*old_path);
}

int	home_is_set(t_shell *shell, char **new_path)
{
	char	*home;

	home = get_env(shell, "HOME");
	if (home)
		home = ft_strdup(home);
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	*new_path = home;
	return (1);
}

int	valid_args(t_shell *shell, char **argv, char **new_path)
{
	if (!argv[1] && home_is_set(shell, new_path))
		return (1);
	if (!argv[1] || *argv[1] == 0)
		return (0);
	if ((ft_strncmp(argv[1], "--", 3) == 0)
		|| (ft_strncmp(argv[1], "~", 2) == 0))
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

//    Returns 0 if the directory is changed, and if $PWD is set successfully when
//    -P is used; non-zero otherwise.
//	  still have to handle options, what error message should we print ?
int	ft_cd(t_shell *shell, char **argv)
{
	char	*new_path;
	char	*old_path;

	new_path = NULL;
	if (argv[1] && ft_strncmp(argv[1], "./", 3) == 0)
		return (-1);
	if (valid_args(shell, argv, &new_path))
	{
		old_path = getcwd(NULL, 0);
		if (chdir(new_path) == -1)
		{
			free_set_null((void **)&old_path);
			free_set_null((void **)&new_path);
			dprintf(2, "minishell: cd: %s: %s\n", argv[1], strerror(errno));
			return (-1);
		}
	}
	else
		return (-1);
	add_old_path_to_env(shell, &old_path);
	add_new_path_to_env(shell, &new_path);
	return (0);
}
