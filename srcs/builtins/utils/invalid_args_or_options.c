/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_args_or_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 16:24:31 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/23 14:09:36 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_name(char *argv, char *built_name)
{
	if (!ft_isalpha(*argv) && *argv != UNDERSCORE)
		return (0);
	if (ft_isalpha(*argv) || *argv == UNDERSCORE)
		argv++;
	if (ft_isdigit(*argv))
		return (0);
	while (ft_isalnum(*argv) || *argv == UNDERSCORE)
		argv++;
	if (ft_strncmp(built_name, "export", 6) == 0
		&& (*argv == '=' || ft_strncmp(argv, "+=", 2) == 0))
		return (1);
	if (*argv)
		return (0);
	return (1);
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
		else if (builtin_type == EXPORT)
			ft_printf(STDERR_FILENO, "export: usage: export [name[=value]\
 ...]\n");
		else if (builtin_type == UNSET)
			ft_printf(STDERR_FILENO, "unset: usage: unset [name ...]\n");
		return (2);
	}
	return (IS_VALID);
}
