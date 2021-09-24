/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:01:41 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:36:27 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (flag == SEMICOLON)
		cpy->redir = flag;
	else if (flag >= IS_REDIR)
		cpy->redir = flag;
	else
		cpy->redir = 0;
}

void	erase_current_cmd(t_token **cmd_array, int i, t_shell *shell)
{
	t_token		*to_erase;

	to_erase = cmd_array[i];
	while (cmd_array[i])
	{
		cmd_array[i] = cmd_array[i + 1];
		i++;
	}
	erase_cmd(to_erase);
	(void)shell;
}

int	insert_home_directory_in_str(t_shell *shell, char **str)
{
	char	*home_dir;
	char	*tmp;
	size_t	len;

	home_dir = ft_strjoin(get_env(shell, "HOME"), "/");
	len = ft_strlen(home_dir);
	tmp = ft_strjoin(home_dir, (*str) + 2);
	free((*str));
	free(home_dir);
	(*str) = tmp;
	return (len);
}

int	process_tilde(t_shell *shell, int *i, char **tk_cpy)
{
	if (ft_strncmp((*tk_cpy), "~", 2) == 0
		|| ft_strncmp((*tk_cpy), "~/", 3) == 0)
	{
		free((*tk_cpy));
		(*tk_cpy) = ft_strdup(get_env(shell, "HOME"));
		return (TRUE);
	}
	else if (ft_strncmp((*tk_cpy), "~/", 2) == 0)
	{
		*i += insert_home_directory_in_str(shell, &(*tk_cpy));
		return (TRUE);
	}
	return (FALSE);
}

//this function only treats the case when ther is $ followed by " or '
//OUTSIDE of any opening quotes
int	dollar_sign_followed_by_quote(char *tk_cpy, const int i)
{
	if (tk_cpy[i] == '$' && (tk_cpy[i + 1] == DOUBLE_QUOTE || \
	tk_cpy[i + 1] == SINGLE_QUOTE))
		return (1);
	return (0);
}
