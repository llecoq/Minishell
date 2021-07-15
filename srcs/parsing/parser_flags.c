/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:00:50 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/15 18:43:37 by abonnel          ###   ########.fr       */
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
			cpy->fd = 0;
			cpy = cpy->next;
		}
		i++;
	}
}

void	set_redir_arg_flags(t_token **cmd_array)
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

void	set_flag_after_redirection(t_token **cmd_array, char **error_str)
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
