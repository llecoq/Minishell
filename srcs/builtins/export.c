/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:32:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/28 18:34:59 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash : export dklfds     ajoute dans export mais pas dans env
// bash export jkjds=65     ajoute dans env
// check si la variable existe deja = géré dans put_env
// A GERER == ARGS / options
// CREER UNE LISTE EXPORT ?

int	export(t_shell *shell, char const **argv)
{
	put_env(shell, argv[1]);
	return (0);
}