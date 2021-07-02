/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/02 16:19:06 by abonnel          ###   ########.fr       */
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

static void	turn_on_flag(int flag, t_token *cpy)
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

static int	after_redir(t_token **cpy, t_token *next_cmd)
{
	t_token		*next_token;
	
	next_token = (*cpy)->next;
	if (is_redirection((*cpy)->word, 0) == PIPE && next_cmd == NULL)
		return (NOTHING_AFTER_REDIR);
	else if (is_redirection((*cpy)->word, 0) != PIPE)
	{
		if (next_token == NULL)
			return (NOTHING_AFTER_REDIR);
		*cpy = (*cpy)->next;
		turn_on_flag(REDIR, *cpy);
	}
	return (1);
}

static int	set_flags(t_token **cmd_array)
{
	int			i;
	t_token		*cpy;
	
	initialize_flags_values(cmd_array);
	i = 0;
	while (cmd_array[i])
	{
		cpy = cmd_array[i];
		turn_on_flag(CMD, cpy);
		cpy = cpy->next;
		while (cpy)
		{
			if (is_redirection(cpy->word, 0))
			{
				turn_on_flag(REDIR, cpy);
				if (after_redir(&cpy, cmd_array[i + 1]) == NOTHING_AFTER_REDIR)
					return (NOTHING_AFTER_REDIR);			
			}
			else
				turn_on_flag(ARG, cpy);
			cpy = cpy->next;
		}
		i++;
	}
	return (1);
}


/*---------------------------------------------------------------------------*/
/*-------- CHECK REDIRECTION IS ONLY ONE WORD -------------------------------*/
/*---------------------------------------------------------------------------*/

/*
The word following the redirection operator in the following descriptions,
is subjected to parameter expansion
If it expands to more than one word, Bash reports an error.
It is done before var expansion bc error needs token->word value
before expansion

bash-3.2$ export VARR="bonjour comment"
bash-3.2$ echo < $VARR
bash: $VARR: ambiguous redirect
*/

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

/*---------------------------------------------------------------------------*/
/*------------------- VAR EXPANSION -----------------------------------------*/
/*---------------------------------------------------------------------------*/

//REPLACE ENV VAR BY THEIR VALUES
//For var that does not exist, just prints nothing

//Outermost quotes are the one that defines behavior :
// echo "aa $USER '$USER' lol"
// aa abonnel 'abonnel' lol

// Var name :
// A word consisting solely of letters, numbers, and underscores
// and beginning with a letter or underscore.
// If char following $ is not a letter or underscore then $ + this following
// char expand to nothing

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
	if (!(ft_isalpha((*str)[i + j]) || (*str)[i + j] == '_')) //if doesn't start by letter or _
	{
		ft_memmove(*str + i, *str + i + 2, ft_strlen(*str));
		return (1);
	}
	while (ft_isalnum((*str)[i + j]) || (*str)[i + j] == '_') //j goes at the end of var name
		j++;
	value = get_var_value(i, j, *str, shell);
	if (!value) //if var does not exist, replace var name by nothing in str
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
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
			{	
				if (str[i] == '$' && str[i + 1])
					i += insert_var_in_str(&str, i, shell);
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '$' && str[i + 1])
			i += insert_var_in_str(&str, i, shell);
		i++;
	}
	return (str);
}

/*-------------- EVERYTHING BEFORE THIS HAS BEEN TESTED ---------------------*/
/*-------------- APRES VACANCES - FAIRE BELOW -------------------------------*/

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

/*---------------------------------------------------------------------------*/
/*------------------- PARSING LAUNCHER --------------------------------------*/
/*---------------------------------------------------------------------------*/

static void token_syntax_processing(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;
	
	i = 0;
	while (cmd_array[i])
	{
		token = cmd_array[i];
		while (token)
		{	
			if (token->redir == 1 && !is_redirection(token->word, 0))//not enough, refer to comment in parse() below
				verify_redir_is_one_word(token->word, shell);
			token->word = process_variables(token->word, shell);
			//dprintf(1, "token = %s\n", token->word);
			//trim_quotes(token->word);
			token = token->next;
		}
		i++;
	}
}



/*
Pour RETOUR DE VACANCES :
Continuer a regarder la gestion d'erreur avant de continuer a implementer (voir commentaire
dans parse()
Avant de trim quotes, cmd verification et char **argv creation
*/
void	parse(t_shell *shell)
{
	/*
	!! error handling, it does not stop program, other parser error will display
	and be added to one another
	
	bash-3.2$ echo < $VARR | txt.txt
	bash: $VARR: ambiguous redirect
	bash: txt.txt: command not found

	below shows that ambiguous redirect has precedence over 
	bash-3.2$ echo >
	bash: syntax error near unexpected token `newline'
	
	bash-3.2$ echo > $5
	bash: $5: ambiguous redirect
	
	*/
	//we need to check if there is NOTHING_AFTER_REDIR after we do syntax processing
	//bc amiguous redirect has more priority than echo >
	//beware that there aren't 2 errors for
	//echo >			and 			echo >$5 		as shown before
	//so check this within same function -> /!\ ambiguous reidrect error display
	//needs token before expansion
	if (set_flags(shell->cmd_array) == NOTHING_AFTER_REDIR)
	{
		error(shell, NOTHING_AFTER_REDIR, NULL);
		return ;
	}
	token_syntax_processing(shell->cmd_array, shell);
	//dprintf(1, "END OF PARSE()\n");
}