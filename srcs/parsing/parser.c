/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/06/25 14:41:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
→**Adds flags to the linked list** :

cmd

arg → 1 = regular arg / 2 = option / 3 = env variable (/ 4 = input redirection / 5 = Heredoc )?

redirection → 1 = pipe / 2 = > / 3 = >>

other flag for < et << because they don't need a dup2() pipe() fork() ? 

- LQ : I did create the fct : int	search_for_builtins(t_shell *shell, t_token *cmd_array)
→ **Verify if each CMD token is** **true** : echo / cd / pwd/ export / unset/ env / exit,
otherwise look through paths and **save path in node**. 
Else : free and "zsh: command not found: lsls" 

- AB : Search if built-in program exists

→ **Create char **argv** : count how many items there are before a redirection or the end 
of the linked list, malloc that to argv[] and then copy the pointers present in our linked 
list to argv[0], argv[1] etc. argv[0] being the command name
*/

/*
first token is always a cmd

-----------
Check if after a redirection or pipe there is no next command
bash-3.2$ ls -la | wc >
bash: syntax error near unexpected token `newline'

bash-3.2$ ls -la | wc |
> bash: syntax error: unexpected end of file
-------------

The parser will trim out the ' et " 
cd "Documents"/42cursus fonctionne ! -> cherche cd Documents/42cursus

Remove "" ' and instead create flag? for easier printing later ? voir execve() quand 
on lui envoi char **argv si dans argv on a les quotes ou pas
trimming seems like a good idea


*/

void	parse(t_shell *shell)
{
	
}//prendre tout d'un bloc "hjhjkd"haah = un seul token