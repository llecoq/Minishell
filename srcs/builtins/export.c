/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:32:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/30 20:24:36 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// name :
// A word consisting solely of letters, numbers, and underscores, and beginning with
// a letter or underscore. Names are used as shell variable and function names. Also
// referred to as an identifier.

// doit print export avec commande EXPORT seulement
// doit gerer export name=value et export name



// export NAME=KJH jkhj jkg (avec espaces, géré par le parser ?)

// char	*join_args(char **argv)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*full_arg;

// 	i = 0;
// 	while (argv[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		full_arg = ft_strdup(argv[1]);
// 		i = 1;
// 		while (argv[++i])
// 		{
// 			tmp = full_arg;
// 			full_arg = ft_strjoin(full_arg, argv[i]);
// 			if (full_arg)
// 				free(tmp);
// 		}
// 		return (full_arg);
// 	}
// 	return (ft_strdup(argv[1]));
// }

int	ft_export(t_shell *shell, char **argv)
{
	// char	*variable_value;
	
	if (invalid_args_or_options(argv, "export"))
		return (-1);
	if (!argv[1])
		return (dprintf(1, "need to print export list\n"));
	if (valid_name(argv[1], "export"))
	{
		// variable_value = join_args(argv);
		// dprintf(1, "full = %s\n", variable_value);
		put_env(shell, argv[1]);
		// free(variable_value);
	}
	else
		dprintf(2, "minishell: export: `%s': not a valid identifier", argv[1]);
	return (0);
}
