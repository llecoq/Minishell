/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/16 10:53:07 by llecoq           ###   ########.fr       */
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
				break;
			}
			token = token->next;
		}
		i++;
	}
}

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
	Errors FROM DIFFERENT COMMANDS add to each other but if there are 2 errors WITHIN ONE CMD
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
	
	Cas avec erreur : Ici on voit que last.txt n'a pas ete cree car il vient apres 
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
		

	bash-3.2$ cat hoho <txt.txt < $VAR
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

	est-ce qu'il faut d'abord tout expandre SAUF les redirections a garder pour plus tard?
	-> de toute facon on n'a pas besoin des redirections pour creer char **argv qui ne les
	incluent pas
	-> comme ca quand l'erreur liee a l'expansion d'une VAR de redirection error, on s'arrete bien
	au bon moment du process

		bash-3.2$ rm *
		bash-3.2$ blabla hoho > txt.txt
		bash: blabla: command not found
		bash-3.2$ ls
		txt.txt
	montre que les fichiers de redir sont crees avant meme que l'existence de la cmd soit checkee
*/

/*
Montre qu'entre quotes on garde les espaces de variables mais hors quotes alors les espaces
sont trimes --> DONC les var SIMPLES/sans quotes sont sujettes a etre casses en multiples 
nodes
bash-3.2$ export VAR="bonjour             espaces"
bash-3.2$ echo llaa$VAR*OO
llaabonjour espaces*OO
bash-3.2$ echo "llaa$VAR*OO"
llaabonjour             espaces*OO
*/

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
		4) Trim quotes
		5) Check si la commande existe juste avant de la lancer mais APRES les redirections
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

static void	remove_quotes_char(char *word, t_shell *shell)
{
	int			i;
	char		closing_quote;
	
	i = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
		{
			closing_quote = word[i];
			ft_memmove(word + i, word + i + 1, ft_strlen(word));
			while (word[i] && word[i] != closing_quote)
				i++;
			if (word[i] == closing_quote)
				ft_memmove(word + i, word + i + 1, ft_strlen(word));
		}
		i++;
	}
	(void)shell;
}

void	remove_quotes(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;
	
	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			remove_quotes_char(token->word, shell);
			token = token->next;
		}
		i++;
	}
}

// pblm avec "bonjour    avec " les cho | cat > file | "onnnnnnnn hehe" "$VAR"
//pete au niveau du main a clear non essential memory
//c'est comme si onnnnnnn hehe n'etait pas malloc -> du au memmove?
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
	split_multiple_words_into_token(shell);
	first_word_is_cmd_flag(shell->cmd_array);
	//Pipe creation();?? ou vraiment en amont juste apres tokenizer
	//!! si c'est le cas au fait que les cmd contenant des erreurs vont etre supprimees
	//a l'etape suivante
	check_and_create_redirections(shell->cmd_array, shell);
	//remove_quotes(shell->cmd_array, shell);
	//print_cmd_array(shell->cmd_array, 1); // A SUPPRIMER

	
	//look_for_command(shell->cmd_array, shell);
	//create char **argv
	//-->EVALUATOR--> execution de la commande sur la toute derniere redirection
	//print_cmd_array(shell->cmd_array, 1); // A SUPPRIMER
}

/*
Errors :
	if SYNTAX ERROR (NOTHING_AFTER_REDIR) then subsequent errors won't display / parser is stopped
	SYNTAX ERROR is checked right after flags are set
		bash-3.2$ echo > | hehe
		bash: syntax error near unexpected token `|'
		---- Nothing is displayed about "hehe"
		---- The error msg displays the token right after redir
		---- SYNTAX ERRROR is checked before all the other errors
	!DONE!
*/

/*---------------------------------------------------------------------------*/
/*------------------- TRIM QUOTES -------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*
TRIM OUTER QUOTES
trim ' et " sur tous les tokens !! on ne trim pas tous les " et '
on les trim 2 a deux
donc le long du token des qu'on en trouve un on va chercher le closing one
et on enleve juste ce "couple" et ainsi de suite
si token = "" then becomes nothing
*/

/*---------------------------------------------------------------------------*/
/*------------------- CMD VERIFICATION---------------------------------------*/
/*---------------------------------------------------------------------------*/

/*
Check if cmd is a word -> see definition

Verify that each token with the flag CMD is true : 
	echo / cd / pwd/ export / unset/ env / exit,

Otherwise look through $PATH and save path in node->cmd_path. 

Else : free and "zsh: command not found: lsls"
refer to minishell notion.so for implementation + Louis had created a
function for that already

Ici pas d'erreur pour $5 alors que ce n'est pas une commande qui existe
si cmd == '\0' alors pas de message d'erreur
bash-3.2$ rm *
bash-3.2$ echo lala | $5
bash-3.2$ ls
bash-3.2$

Alors que si var non vide on a bien un msg d'erreur si cmd n'existe pas
bash-3.2$ export VAR=noexist
bash-3.2$ echo lala | $VAR
bash: noexist: command not found

Visiblement quand un token est = '\0' alors on ne le cherche pas
bash-3.2$ $5 lala
bash: lala: command not found

Donc des qu'un token qui n'est pas une redirection devient '\0' apres var
expansion on l'enleve de la liste AVANT de set le flag cmd ou autre
*/

/*---------------------------------------------------------------------------*/
/*------------------- CHAR **ARGV CREATION ----------------------------------*/
/*---------------------------------------------------------------------------*/

/*
si aucune commande dans cmd_array alors clean non essential et retour a prompt
sans msg d'erreur ex : $4 $4

CREATE char **argv : nb of arg = nb of token with flags cmd and arg
We do not include redirections tokens in char **argv
We can just make the argv[] point to the adress of token? 
instead of duplicating memory

bash-3.2$ cat othertxt.txt
lalala
bash-3.2$ export VAR="othertxt.txt  otherfile "
bash-3.2$ cat $VAR | grep "lala"
cat: otherfile: No such file or directory
lalala

bash-3.2$ ls
hoho	txt.txt
bash-3.2$ cat "hoho     txt.txt"
cat: hoho     txt.txt: No such file or directory
bash-3.2$ export VAR="hoho   txt.txt"
bash-3.2$ cat $VAR
blablbalba
chat et chien
bash-3.2$ echo $VAR
hoho txt.txt
--> spaces are skiped in echo so it means that Vars that are expanded to 2 words
are then considered to be 2 tokens alors que un token qui faisait deja
plusieurs mots (entre " ou ') reste bien integre = un seul et mm token

dans draftminishell : exec_cat.c j'ai bien verifie, si on lui envoie 
char **argv = {"cat", "file1 file2", NULL} ca ne fonctionnera pas meme si file1 et file2
existent donc il faut bien split en deux parametres differents
*/
