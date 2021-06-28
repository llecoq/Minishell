/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/28 17:11:00 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
------------------------------------------------------------------------------------------
→**Adds flags to the linked list** :

cmd = very first token of every *cmd_array[]

arg

redirection → | > >> < << 
Dans cas des redirections (pas du pipe), le token (1 seul) qui vient juste apres sera 
un flag REDIRECTION et pas un arg (de toute facon apres pipe on a NULL)
-> pour calcul ensuite du nb d'argv et pour qu'il ne soit pas mis dans char **argv

-----------------------------------------------------------------------------------------
→ **Verify if each CMD token is** **true** : echo / cd / pwd/ export / unset/ env / exit,
otherwise look through paths and **save path in node**. 
Else : free and "zsh: command not found: lsls" 
Fonction faite par LQ pour nos built ins

Check if after a redirection or pipe there is no next command
bash-3.2$ ls -la | wc >
bash: syntax error near unexpected token `newline'

bash-3.2$ ls -la | wc |
> bash: syntax error: unexpected end of file

----------------------------------------------------------------------------------------
→ CREATE char **argv : nb of arg = cmd + nb of flag arg

in case command is only spaces, in bash it IS a command so I did create a cmd_array for it

We only put cmd and args flags in char **argv

Before putting in argv, trim out the ' and " and for " replace the $env var
cd "Documents"/42cursus fonctionne ! -> cherche cd Documents/42cursus

---------------------------------------------------------------------------------------
*/

void	parse(t_shell *shell)
{
	
}