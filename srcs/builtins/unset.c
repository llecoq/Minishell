/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:42:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/07 10:07:00 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// name :
// A word consisting solely of letters, numbers, and underscores, and beginning with
// a letter or underscore. Names are used as shell variable and function names. Also
// referred to as an identifier.
int	valid_name(char *argv, char *built_name)
{
	if (!ft_isalpha(*argv) && *argv != '_')
		return (0);
	if (ft_isalpha(*argv) || *argv == '_')
		argv++;
	if (*argv >= '0' && *argv <= '9')
		return (0);
	while (ft_isalnum(*argv) || *argv == '_')
		argv++;
	if (ft_strncmp(built_name, "export", 6) == 0
		&& (*argv == '=' || ft_strncmp(argv, "+=", 2) == 0))
		return (1);
	if (*argv)
		return (0);
	return (1);
}

void	unset_variable(t_shell *shell, t_list *env_list, char *name)
{
	char	*content;
	size_t	len;

	len = ft_strlen(name);
	while (env_list)
	{
		content = (char *)env_list->content;
		if (ft_strncmp(name, content, len) == 0 && content[len] == '=')
		{
			env_list->variable = IS_UNSET;
			if (shell->path && ft_strncmp(content, "PATH=", 5) == 0)
				shell->path->variable = IS_UNSET;
			return ;
		}
		env_list = env_list->next;
	}
}

int	invalid_args_or_options(char **argv, char *name, int builtin_type)
{
	if (argv[1] && *argv[1] == '-')
	{
		ft_printf(2, "minishell: %s: -%c: invalid option\n", name, argv[1][1]);
		if (builtin_type == PWD)
		{
			ft_printf(STDERR_FILENO, "pwd: usage: pwd\n");
			return (1);
		}
		if (builtin_type == EXPORT)
			ft_printf(STDERR_FILENO, "export: usage: export [-nf] [name[=value] ...] or export -p\n");
		else if (builtin_type == UNSET)
			ft_printf(STDERR_FILENO, "unset: usage: unset [-f] [-v] [name ...]\n");
		// else
		// 	ft_printf(2, "%s: usage: %s [name ...]\n", name, name);
		return (2);
	}
	return (IS_VALID);
}
// The unsetenv() function deletes the variable name from the environment. If name
// does not exist in the environment, then the function succeeds, and the environment
// is unchanged.
// The unsetenv() function returns zero on success, or -1 on error, with errno set
// to indicate the cause of the error.
int	ft_unset(t_shell *shell, char **argv)
{
	if (invalid_args_or_options(argv, "unset", UNSET))
		return (INVALID_ARGS_OR_OPTIONS);
	if (!argv[1])
		return (0);
	if (argv[1] && valid_name(argv[1], "unset"))
	{
		unset_variable(shell, shell->env_list, argv[1]);
		unset_variable(shell, shell->export_list, argv[1]);
	}
	else
	{
		ft_printf(2, "minishell: unset: `%s': not a valid identifier\n", argv[1]);
		return (1);
	}
	store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
	return (0);
}
