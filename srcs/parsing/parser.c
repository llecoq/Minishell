/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/18 18:37:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
lire : https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Executing-Commands
*/

static void	first_word_is_cmd_flag(t_token **cmd_array)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->arg == 1)
			{
				turn_on_flag(CMD, token);
				break ;
			}
			token = token->next;
		}
		i++;
	}
}

//une commande ne sera jamais vide car il restera toujours le token du pipe
void	remove_empty_tokens(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;

	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->word[0] == '\0')
				erase_token(&token, &cmd_array[i], shell);
			else if (token)
				token = token->next;
		}
		i++;
	}
}

/*	
	Donc deroulement du parsing :
	
NO		NB : le dernier token qui contient le pipe est inutile puisque chaque cmd_array est
NO		necessairement separé par un pipe --> PAS FAIT CAR BESOIN DU PIPE POUR nothing_after_redir
OK		0) Mettre les flags redir et arg seulement (car la premier var peut etre une cmd du type : 
OK		CMDNAME="echo     haha")
OK		1)toutes les var qui ne sont pas des redir sont expandues
OK		1bis)si elles font plusieurs mots il faut les splitter en x tokens (seulement les var, pas 
		les tokens simples) et les ajouter a la liste (ajout de maillon)
OK		2) Si le premier token/word n'a pas le flag REDIR on alors on set son flag a CMD sinon on laisse
		tel quel.
		Une cmd_array peut commencer par une redirection par contre si il commence par une var qui contient
		une redir alors il aura le flag ARG et on aura msg d'erreur bash: >>: command not found
		bash-3.2$ >> haha				<--fonctionne
		bash-3.2$ export REDIR=">>"		<--ne fonctionne pas
		bash-3.2$ $REDIR loool
		Donc on regarde bien juste le flag, ne pas faire is_redirection(first_token)
		3)avant l'execution de la commande les redirections sont crees de gauche a droite: 
OK			a) la premiere est cree : VAR expandues, si pas d'erreur d'expansion, le fichier est 
			cherché et si n'existe pas il est cree. Pour ca on utilise open() et selon si redir < ou >
			alors open(O_CREAT, O_TRUNC) et si redir << ou >> open(O_CREATE) comme ca le contenu sera bien
			overwritten quand il doit l'etre
OK			c) la deuxieme redir (de gauche a droite) est cree, 
				si erreur on arrete tout ici
				si pas d'erreur alors crea de redir suivante et ainsi de suite
OK			Si erreur au cours de l'ouverture/crea d'un des fichiers alors cette commande ne sera
			pas executee, effacer cette cmd de cmd_array?
OK		4) Trim quotes
OK		5) Check si la commande existe juste avant de la lancer mais APRES les redirections
		6)char **argv est cree
EVAL	7) la commande est executee SUR LA TOUTE DERNIERE REDIRECTION, les autres sont "ignorees", seuls
		les fichiers ont etes crees donc /!\ a la gestion des fd qu'il faudra bien close
		NON! pour << HEREDOC, toutes les redirections sont prises en compte mais heredoc ne cree pas de 
		fichier qui "reste", peut etre un fichier temporaire ou un buffer?
EVAL	8) on passe a la commande suivante
		
			bash-3.2$ echo < othertxt.txt > hehe
			bash-3.2$ ls
			hehe		hihi		othertxt.txt	txt.txt
			bash-3.2$ cat hehe
		FAUX : Montre que la commande est bien executee seulement sur la derniere redirection (mais les fichiers
		intermediaires sont bien crees) puisque c'est comme si on avait fait echo > hehe
		FAUX car echo ignore les input redir d'ou l'impression qu'il n'y a que la derniere redir qui est
		executee	

*/

void	parse(t_shell *shell)
{
	char		*no_token_after_redir;

	set_redir_arg_flags(shell->cmd_array);
	no_token_after_redir = NULL;
	set_flag_after_redirection(shell->cmd_array, &no_token_after_redir);
	if (no_token_after_redir)
	{
		err_clear(shell, NOTHING_AFTER_REDIR, no_token_after_redir);
		free(no_token_after_redir);
		return ;
	}
	arg_syntax_processing(shell->cmd_array, shell);
	remove_empty_tokens(shell->cmd_array, shell);
	split_multiple_words_into_tokens(shell);
	first_word_is_cmd_flag(shell->cmd_array);
	remove_quotes(shell->cmd_array, shell);
	// print_cmd_array(shell->cmd_array, 1);
	create_empty_cmds_list(shell, shell->nb_of_cmds);
	create_argument_list(shell->cmd_array, shell);
	create_heredoc(shell, shell->cmd_array, shell->cmds_list);
}

//OK en dessous--------------------------------------------------------------

/*
Vendredi 16 Juillet avant de faire char **argv a 17h20

OK Ici pas d'erreur pour $5 alors que ce n'est pas une commande qui existe
si cmd == '\0' alors pas de message d'erreur
bash-3.2$ rm *
bash-3.2$ echo lala | $5
bash-3.2$ ls
bash-3.2$

OK Alors que si var non vide on a bien un msg d'erreur si cmd n'existe pas
bash-3.2$ export VAR=noexist
bash-3.2$ echo lala | $VAR
bash: noexist: command not found

OK Visiblement quand un token est = '\0' alors on ne le cherche pas
bash-3.2$ $5 lala
bash: lala: command not found

Donc des qu'un token qui n'est pas une redirection devient '\0' apres var
expansion on l'enleve de la liste AVANT de set le flag cmd ou autre
*/

/*
OK	Errors FROM DIFFERENT COMMANDS add to each other but if there are 2 errors WITHIN ONE CMD
	only the first one/error msg appears
	Even if there is an error on one command, the next cmd will be executed

		bash-3.2$ echo < $VARR | txt.txt
		bash: $VARR: ambiguous redirect
		bash: txt.txt: command not found

		bash-3.2$ echo haha > $5 | echo haha
		bash: $5: ambiguous redirect
		haha		
	
	Cas sans erreur : Trois fichiers sont crees et c'est le dernier qui contiendra "lalala",
	les autres sont vides
	
		bash-3.2$ rm *
		bash-3.2$ echo lalala > txt.txt > hihi > othertxt.txt
		bash-3.2$ ls
		hihi		othertxt.txt	txt.txt
	
OK	Cas avec erreur : Ici on voit que last.txt n'a pas ete cree car il vient apres 
	un ambiguous redirect. Montre que les redir ne sont expandues qu'au moment meme ou elles
	doivent etre executees/la redir doit etre cree -> car elles ne sont pas inclues comme des arg
	dans char **argv. 
		
		bash-3.2$ rm *
		bash-3.2$ echo lalala > txt.txt > $OTHERVAR > last.txt
		bash: $OTHERVAR: ambiguous redirect
		bash-3.2$ ls
		txt.txt
		bash-3.2$ cat txt.txt
		bash-3.2$
		

OK	bash-3.2$ cat hoho <txt.txt < $VAR
	bash: $VAR: ambiguous redirect
	-->ambiguous redirect stop meme cat hoho
	bash-3.2$ cat hoho <txt.txt
	blablbalba
	bash-3.2$ cat hoho
	blablbalba
	bash-3.2$ cat txt.txt
	elephant
	bash-3.2$ cat hoho <bonjour <$VAR
	bash: bonjour: No such file or directory
	Ici on voit qu'on n'arrive pas a <$VAR et sachant que les redirections sont faites AVANT les
	arguments normaux, on voit bien que la commande est stoppee au moment ou une erreur apparait
	
	bash-3.2$ cat file_that_no_exist <no_exist <$VAR
	bash: no_exist: No such file or directory
	Ici ca confirme ca : le fichier file_that_no_exist n'a pas ete testé, c'est au moment de creer
	la redirection (pipe dup) que no_exist est testé -> erreur -> arret du process

		bash-3.2$ rm *
		bash-3.2$ blabla hoho > txt.txt
		bash: blabla: command not found
		bash-3.2$ ls
		txt.txt
	montre que les fichiers de redir sont crees avant meme que l'existence de la cmd soit checkee
*/
