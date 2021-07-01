/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 12:01:55 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/01 16:15:05 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
The word following the redirection operator in the following descriptions,
is subjected to parameter expansion
If it expands to more than one word, Bash reports an error.
-----------------------------------------------------------------------------------------
→ **Verify if each CMD token is** **true** : echo / cd / pwd/ export / unset/ env / exit,
otherwise look through paths and **save path in node**. 
in case command is only spaces, in bash it IS a command so I did create a cmd_array for it
but program goes back to prompt when only space

Else : free and "zsh: command not found: lsls" 

----------------------------------------------------------------------------------------
→ CREATE char **argv : nb of arg = cmd + nb of flag arg


We only put cmd and args flags in char **argv
---------------------------------------------------------------------------------------
*/

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

//------------------------------------------------------------------------------
//REPLACE ENV VAR BY THEIR VALUES
//ce sont les outmost outer quotes qui donnent le ton
//Entrer dans fonction selon les cas
//si entre '' on avance jusqu'a prochaine closing one sans regarder ce qu'il y a entre les deux
//si entre "" ou pas entre quotes n'importe quelle var d'env rencontree sera a remplacer

//for var that does not exist, just prints nothing

// echo "aa $USER '$USER' lol"
// aa abonnel 'abonnel' lol

//!! 
// echo bonr"hihi $USER'$USER"
// bonrhihi abonnel'abonnel
// echo "bonjour$USER#lol"
// bonjourabonnel#lol
//ATTENTION, var name est delimité soit par un espace apres le nom soit n'importe quel char
//non alphanumerique except underscore
// name :
// A word consisting solely of letters, numbers, and underscores, and beginning with
// a letter or underscore. Names are used as shell variable and function names. Also
// referred to as an identifier.

//!! si chiffre apres $mange le premier chiffre et laisse le reste intact
// bash-3.2$ echo "bonjour$456USER-lol"
// bonjour56USER-lol
// bash-3.2$ echo "bonjour$56USER-lol"
// bonjour6USER-lol
// bash-3.2$ echo "bonjour$6USER-lol"
// bonjourUSER-lol

// -----------------------------------------------------------------------------------------
// 
// The word following the redirection operator in the following descriptions,
// is subjected to parameter expansion
// If it expands to more than one word, Bash reports an error.
//-----------------------------------------------------------------------------
//TRIM OUTER QUOTES
//trim ' et " sur tous les tokens !! on ne trim pas tous les " et '
//on les trim 2 a deux
//donc le long du token des qu'on en trouve un on va chercher le closing one
//et on enleve juste ce "couple" et ainsi de suite
//si token = "" alors becomes a space
// -----------------------------------------------------------------------------------------

//!! strlen de null fait segfault


static char	*get_var_value(int i, int j, const char *str, t_shell *shell)
{
	char		*var_name;
	char		*var_value;

	var_value = NULL; //a enlever?
	var_name = calloc_sh(shell, sizeof(char) * j + 2); //+2 because1 for $ char and 1 for \0
	ft_strlcpy(var_name, str + i + 1, j + 2);
	ft_printf(1, "var_name = %s\n", var_name);
	return (var_value);
	(void)shell;
}


//!! $$ = 810 
//echo $$ 
//bash 810
//i starts at $
static int	insert_var_in_str(char *str, const int i, t_shell *shell)
{
	int			j;
	int			value_len;
	char		*dst;
	char		*value;

	j = 1; // to start after $
	if (!(ft_isalpha(str[i + j]) || str[i + j] == '_')) //if doesn't start by letter or _
	{
		//if $$ alors il faut inserer 810
		ft_memmove(str + i, str + i + 2, ft_strlen(str));//test if strlen == 0
		return (2);
	}
	while (ft_isalnum(str[i + j]) || str[i + j] == '_')
		j++;
	dprintf(1, "str + i + j = %s\n", str + i + j); //devrait etre apres le name
	value = get_var_value(i, j, str, shell);
	//value_len = len(value); !!! value peu etre null donc strlen va segfault
	//new_str = malloc(len(str) + len(value) - (j))
	//strlcpy(new_str, str, i)
	//strlcat(new_str + i, value, len(new_str + value))
	//strlcat(new_str + len(new_str) + len(value), str + i + j, new_str size)
	//free(value)
	//free(str)
	//str = new_str
	//return (value_len)
	(void)value;
	(void)value_len;
	(void)j;
	(void)dst;
	(void)shell;
	return (0);
}


//We must restart at i + var value length bc otherwise it will interpret things it
//should not. Variables that reference other var inside of themselves are already
//processed at the export stage

//bash-3.2$ export NEWW='HEHE"$USER"bonjour'
// bash-3.2$ echo "bonjour $NEWW et ensuite on rigole"
// bonjour HEHE"$USER"bonjour et ensuite on rigole
// bash-3.2$ env | grep "NEWW"
// NEWW=HEHE"$USER"bonjour

//In that case up there, if we would restart at the position were $ used to be
//then it will enter "$USER" and would interpret USER whereas it should not
static void	process_variables(char *str, t_shell *shell)
{
	int			i;
	
	i = 0;
	dprintf(1, "str at start= %s\n", str);
	while (str[i])
	{
		//dprintf(1, "char n*%d = %c\n", i, str[i]);
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
			{	
				if (str[i] == '$')
					i += insert_var_in_str(str, i, shell);
					//dprintf(1, "rentre dans dble quotes a %s\n", str + i);
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			i++;
			// dprintf(1, "ici\n");
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '$')
			i += insert_var_in_str(str, i, shell);
			// dprintf(1, "rentre hors quotes a %s\n", str + i);
		i++;
	}
	dprintf(1, "str = %s\n", str);
	(void)shell;//a enlever
}

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
			process_variables(token->word, shell);//??
			dprintf(1, "token = %s\n", token->word);
			//trim_quotes(token->word);	
			token = token->next;
		}
		i++;
	}
}

/* 
We first initialize flags values by default to -1 bc it will allow us to make sure
they have all been properly set
Then we set each to 1 or 0
*/
void	parse(t_shell *shell)
{
	if (set_flags(shell->cmd_array) == NOTHING_AFTER_REDIR)
	{
		error(shell, NOTHING_AFTER_REDIR);
		return ;
	}
	token_syntax_processing(shell->cmd_array, shell);
	//dprintf(1, "END OF PARSE()\n");
}