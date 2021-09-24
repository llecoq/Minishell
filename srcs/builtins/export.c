/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:32:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 15:48:03 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// name :
// A word consisting solely of letters, numbers, and underscores, and beginning
// with a letter or underscore. Names are used as shell variable and function
// names. Also referred to as an identifier.

static void	print_variable_name(char *full_var, int *i)
{
	while (full_var[*i] && full_var[*i] != '=')
	{
		ft_putchar_fd(full_var[*i], 1);
		(*i)++;
	}
}

static void	print_variable_value(char *full_var, int *i)
{
	ft_putstr_fd("=\"", STDOUT_FILENO);
	(*i)++;
	while (full_var[*i])
	{
		ft_putchar_fd(full_var[*i], 1);
		(*i)++;
	}
	ft_printf(STDOUT_FILENO, "\"");
}

static int	print_export_list(t_list *export_list)
{
	int		i;
	char	*full_var;

	while (export_list)
	{
		i = 0;
		if (export_list->variable == IS_SET)
		{
			ft_printf(1, "declare -x ");
			full_var = (char *)export_list->content;
			print_variable_name(full_var, &i);
			if (ft_strncmp(full_var, "OLDPWD=", 8) && full_var[i] == '=')
				print_variable_value(full_var, &i);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		export_list = export_list->next;
	}
	return (0);
}

// attention, export test="ui        ah" non gere
int	ft_export(t_shell *shell, char **argv)
{
	char	*export_name_and_value;

	if (invalid_args_or_options(argv, "export", EXPORT))
		return (INVALID_ARGS_OR_OPTIONS);
	if (argv[1] == NULL)
		return (print_export_list(shell->export_list));
	argv++;
	while (*argv)
	{
		if (valid_name(*argv, "export"))
		{
			export_name_and_value = ft_strdup(*argv);
			g_exit_status = put_env(shell, export_name_and_value);
			free_set_null((void **)&export_name_and_value);
		}
		else
		{
			g_exit_status = 1;
			ft_printf(2, "minishell: export: `%s': not a valid identifier\
\n", *argv);
		}
		argv++;
	}
	return (g_exit_status);
}
