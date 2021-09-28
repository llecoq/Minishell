/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:11:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 16:43:39 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum	e_exit
{
	ARG_IS_NUMERIC = 1,
	ARG_IS_NOT_NUMERIC = 0,
};

static int	arg_is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && (arg[i] == '-' || arg[i] == '+'))
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		return (ARG_IS_NUMERIC);
	return (ARG_IS_NOT_NUMERIC);
}

static int	arg_long_overflow(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	if (i > 19)
		return (1);
	else if (i == 19)
	{
		arg = &arg[i - 1];
		if (ft_atoi(arg) >= 8)
			return (1);
	}
	return (0);
}

static int	process_numeric_arg(char **argv)
{
	if (argv[2])
	{
		ft_printf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	g_exit_status = (unsigned char)ft_atoi(argv[1]);
	if (arg_long_overflow(argv[1]))
	{
		ft_printf(STDERR_FILENO, "minishell: exit: %s: numeric argument\
 required\n", argv[1]);
		g_exit_status = 255;
	}
	return (0);
}

// ft_printf(STDOUT_FILENO, "exit\n"); a enlever si minishell -c
int	ft_exit(t_shell *shell, char **argv)
{
	if (argv && ft_strncmp(argv[0], "exit", 5) == 0)
	{
		if (shell->execute_minishell_from_str == FALSE
			&& shell->child_process == FALSE)
			ft_printf(STDOUT_FILENO, "exit\n");
		if (argv[1] && arg_is_numeric(argv[1]) && process_numeric_arg(argv))
			return (EXIT_FAILURE);
		else if (argv[1] && !arg_is_numeric(argv[1]))
		{
			ft_printf(STDERR_FILENO, "minishell: exit: %s:\
 numeric argument required\n", argv[1]);
			g_exit_status = 255;
		}
	}
	if (argv == NULL && shell->flush_stdin == TRUE)
		ft_printf(STDOUT_FILENO, "exit\n");
	clear_memory(shell);
	exit(g_exit_status);
}
