/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/14 13:37:59 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---------------------------------------------------------------------------*/
/*------------------- FLAG ASSIGNATION---------------------------------------*/
/*---------------------------------------------------------------------------*/

// We first initialize flags values by default to -1 bc it will 
// allow us to make sure they have all been properly set
// Then we set each to 1 or 0


static void	initialize_flags_values(t_token **cmd_array)
{
	int			i;
	t_token		*cpy;

	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		while (cpy)
		{
			cpy->cmd = -1;
			cpy->arg = -1;
			cpy->redir = -1;
			cpy = cpy->next;
		}
		i++;
	}
}

void	turn_on_flag(int flag, t_token *cpy)
{
	if (flag == CMD)
		cpy->cmd = 1;
	else
		cpy->cmd = 0;
	if (flag == ARG)
		cpy->arg = 1;
	else
		cpy->arg = 0;
	if (flag == REDIR)
		cpy->redir = 1;
	else
		cpy->redir = 0;
}

static void	set_redir_arg_flags(t_token **cmd_array)
{
	int			i;
	t_token		*cpy;
	
	initialize_flags_values(cmd_array);
	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		while (cpy)
		{
			if (is_redirection(cpy->word, 0))
				turn_on_flag(REDIR, cpy);
			else
				turn_on_flag(ARG, cpy);
			cpy = cpy->next;
		}
		i++;
	}
}

static char	*create_error_str(char *next_token)
{
	char		*error_str;

	error_str = calloc(ft_strlen(next_token) + 3, sizeof(char));
	error_str[0] = '`';
	ft_strlcat(error_str, next_token, ft_strlen(next_token) + 3);
	error_str[ft_strlen(next_token) + 1] = '\'';
	return (error_str);
}

static char	*check_after_redir(t_token *cpy, t_token *next_cmd)
{
	if (is_redirection(cpy->word, 0) == PIPE && next_cmd == NULL)
		return (create_error_str("newline"));
	else if (is_redirection(cpy->word, 0) != PIPE)
	{
		if (cpy->next == NULL)
			return (create_error_str("newline"));
		else if (cpy->next->redir == 1)
			return (create_error_str(cpy->next->word));
	}
	return (NULL);
}

static void	set_flag_after_redirection(t_token **cmd_array, char **error_str)
{
	int			i;
	t_token		*cpy;
	
	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		while (cpy)
		{
			if (cpy->redir == 1)
			{
				*error_str = check_after_redir(cpy, cmd_array[i + 1]);
				if (*error_str)
					return ;
				if (is_redirection(cpy->word, 0) != PIPE)
				{
					cpy = cpy->next;
					turn_on_flag(REDIR, cpy);//next token is redir
				}
			}
			cpy = cpy->next;
		}
		i++;
	}
}

/*---------------------------------------------------------------------------*/
/*-------- CHECK REDIRECTION IS ONLY ONE WORD -------------------------------*/
/*---------------------------------------------------------------------------*/

/*
man bash :
The word following the redirection operator in the following descriptions,
is subjected to parameter expansion
If it expands to more than one word, Bash reports an error.
It is done before var expansion bc error needs token->word value
before expansion

bash-3.2$ export VARR="bonjour comment"
bash-3.2$ echo < $VARR
bash: $VARR: ambiguous redirect
*/

/*
static void	verify_redir_is_one_word(char *token, t_shell *shell)
{
	int			i;
	char		*variable_value;

	variable_value = process_variables(token, shell);
	if (variable_value == NULL)
		error(shell, REDIR_IS_NOT_ONE_WORD, token);
	i = 0;
	while (token[i])
	{
		if (token[i] == ' ')
			error(shell, REDIR_IS_NOT_ONE_WORD, token);
		i++;
	}
}
*/

/*---------------------------------------------------------------------------*/
/*------------------- VAR EXPANSION -----------------------------------------*/
/*---------------------------------------------------------------------------*/

/*
REPLACE ENV VAR BY THEIR VALUES
For var that does not exist, just prints nothing

Outermost quotes are the one that defines behavior :
echo "aa $USER '$USER' lol"
aa abonnel 'abonnel' lol

Var name :
A word consisting solely of letters, numbers, and underscores
and beginning with a letter or underscore.
If char following $ is not a letter or underscore then $ + this following
char expand to nothing
*/

static char	*get_var_value(int i, int j, const char *str, t_shell *shell)
{
	char		*var_name;
	char		*var_value;

	var_value = NULL;
	var_name = calloc_sh(shell, sizeof(char) * j); //bc j = var_name_len + 1
	ft_strlcpy(var_name, str + i + 1, j);
	var_value = get_env(shell, var_name);
	free(var_name);
	return (var_value);
}

//i starts at $
//echo $$ is not to be handled by us
static int	insert_var_in_str(char **str, const int i, t_shell *shell)
{
	int			j;
	int			dst_len;
	char		*dst;
	char		*value;

	j = 1; // to start after $
	if (!is_word_char((*str)[i + j], FIRST_LETTER)) //if doesn't start by letter or _
	{
		ft_memmove(*str + i, *str + i + 2, ft_strlen(*str));
		return (1);
	}
	while (is_word_char((*str)[i + j], OTHER_LETTERS)) //j goes at the end of var name
		j++;
	value = get_var_value(i, j, *str, shell);
	if (!value) //if !var, replace var name by nothing in str
	{
		ft_memmove(*str + i, *str + i + j, ft_strlen(*str));
		return (0);
	}
	//dst len = src_len + diff between var name and var value + 1 for \0
	dst_len = ft_strlen(*str) - j + ft_strlen(value) + 1;
	dst = calloc_sh(shell, dst_len);
	ft_strlcpy(dst, *str, i + 1); //copy str until $ to dst
	ft_strlcat(dst, value, dst_len); //append var value
	ft_strlcat(dst, *str + i + j, dst_len); //append rest of str
	free_set_null((void **)str);
	*str = dst;
	return (ft_strlen(value) - 1);
}

/*--------------------------PROCESS_VARIABLES() -----------------------------*/		
//We must restart at i + length of var value bc otherwise it will interpret 
//things it should not so we send an int ptr to insert_var_in_str()
//Variables that reference other var inside of themselves are already
//processed at the export cmd stage so appear already fully expanded in env. 

//In the case below, it shows what would happen if we would restart at the 
// position were $ used to be instead of i + length of var value,
// it would enter "$USER" and would interpret USER whereas it should not
// as it was originaly defined as a string literal and should remain so

//bash-3.2$ export NEWW='HEHE"$USER"bonjour'
// bash-3.2$ echo "bonjour $NEWW et ensuite"
// bonjour HEHE"$USER"bonjour et ensuite
// bash-3.2$ env | grep "NEWW"
// NEWW=HEHE"$USER"bonjour
/*---------------------------------------------------------------------------*/

char	*process_variables(char *str, t_shell *shell)
{
	int			i;
	
	i = 0;//pour norminette debuter a -1 et str[++i]
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
			{	
				if (str[i] == '$' && str[i + 1])
					i += insert_var_in_str(&str, i, shell); //ne pas splitter en multiples tokens
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '$' && str[i + 1])// + splitter en multiples tokens
			i += insert_var_in_str(&str, i, shell);
		i++;
	}
	return (str);
}

/*-------------- EVERYTHING BEFORE THIS HAS BEEN TESTED ---------------------*/

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
*/

/*---------------------------------------------------------------------------*/
/*------------------- CHAR **ARGV CREATION ----------------------------------*/
/*---------------------------------------------------------------------------*/

/*
CREATE char **argv : nb of arg = nb of token with flags cmd and arg
We do not include redirections tokens in char **argv
We can just make the argv[] point to the adress of token? 
instead of duplicating memory
*/

/*
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

/*---------------------------------------------------------------------------*/
/*------------------- PARSING LAUNCHER --------------------------------------*/
/*---------------------------------------------------------------------------*/

static void arg_syntax_processing(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;
	
	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->redir == 0)
				token->word = process_variables(token->word, shell);
			//dprintf(1, "token = %s\n", token->word);
			token = token->next;
		}
		i++;
	}
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
lire : https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Executing-Commands
*/

/*	
	Donc deroulement du parsing :
	
NO		NB : le dernier token qui contient le pipe est inutile puisque chaque cmd_array est
NO		necessairement separé par un pipe --> PAS FAIT CAR BESOIN DU PIPE POUR nothing_after_redir
OK		0) Mettre les flags redir et arg seulement (car la premier var peut etre une cmd du type : 
OK		CMDNAME="echo     haha")
OK		1)toutes les var qui ne sont pas des redir sont expandues
		1bis)si elles font plusieurs mots il faut les splitter en x tokens (seulement les var, pas 
		les tokens simples) et les ajouter a la liste (ajout de maillon)
		2) Si le premier token/word n'a pas le flag REDIR on alors on set son flag a CMD sinon on laisse
		tel quel.
		Une cmd_array peut commencer par une redirection par contre si il commence par une var qui contient
		une redir alors il aura le flag ARG et on aura msg d'erreur bash: >>: command not found
		bash-3.2$ >> haha				<--fonctionne
		bash-3.2$ export REDIR=">>"		<--ne fonctionne pas
		bash-3.2$ $REDIR loool
		Donc on regarde bien juste le flag, ne pas faire is_redirection(first_token)
		3)avant l'execution de la commande les redirections sont crees de gauche a droite: 
			a) la premiere est cree : VAR expandues, si pas d'erreur d'expansion, le fichier est 
			cherché et si n'existe pas il est cree. Pour ca on utilise open() et selon si redir < ou >
			alors open(O_CREAT, O_TRUNC) et si redir << ou >> open(O_CREATE) comme ca le contenu sera bien
			overwritten quand il doit l'etre
			c) la deuxieme redir (de gauche a droite) est cree, 
				si erreur on arrete tout ici
				si pas d'erreur alors crea de redir suivante et ainsi de suite
		4) Check si la commande existe juste avant de la lancer mais APRES les redirections
		5)Trim quotes
		6)char **argv est cree
EVAL	7) la commande est executee SUR LA TOUTE DERNIERE REDIRECTION, les autres sont "ignorees", seuls
		les fichiers ont etes crees donc /!\ a la gestion des fd qu'il faudra bien close
EVAL	8) on passe a la commande suivante
		
			bash-3.2$ echo < othertxt.txt > hehe
			bash-3.2$ ls
			hehe		hihi		othertxt.txt	txt.txt
			bash-3.2$ cat hehe
		Montre que la commande est bien executee seulement sur la derniere redirection (mais les fichiers
		intermediaires sont bien crees) puisque c'est comme si on avait fait echo > hehe

*/

static void	first_word_is_cmd_flag(t_token **cmd_array)
{
	//on ne check pas a ce niveau si cmd is a "word"
	// bash-3.2$ 78echo > txt.txt
	// bash: 78echo: command not found
	// bash-3.2$ export VAR="deux mots"
	// bash-3.2$ 78echo > $VAR
	// bash: $VAR: ambiguous redirect
	int			i;
	
	i = 0;
	while (cmd_array[i])
	{
		if (cmd_array[i]->redir == 0)
			turn_on_flag(CMD, cmd_array[i]);
		i++;
	}
}

void	parse(t_shell *shell)
{
	char		*no_token_after_redir;

	set_redir_arg_flags(shell->cmd_array);
	no_token_after_redir = NULL;
	set_flag_after_redirection(shell->cmd_array, &no_token_after_redir);
	if (no_token_after_redir)
	{
		error(shell, NOTHING_AFTER_REDIR, no_token_after_redir);
		free(no_token_after_redir);
		return ;
	}
	arg_syntax_processing(shell->cmd_array, shell);
	split_multiple_words_into_token(shell);
	first_word_is_cmd_flag(shell->cmd_array); //si premier token n'a pas le flag REDIR
	//print_cmd_array(shell->cmd_array, 1); // A SUPPRIMER
	//check_and_create_redirections()
		// if (token->redir == 1 && !is_redirection(token->word, 0))//VERIFY IT WORKS and does not stop parser
			// 	verify_redir_is_one_word(token->word, shell);
	//check cmd exist
	//trim quotes
	//create char **argv
	//-->EVALUATOR--> execution de la commande sur la toute derniere redirection
	//print_cmd_array(shell->cmd_array, 1); // A SUPPRIMER
}