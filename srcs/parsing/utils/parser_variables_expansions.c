/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variables_expansions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:27:35 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:48:03 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*get_errno_value(void)
{
	static char	errno_value[10];
	char		*errno_itoa;
	int			i;
	int			len;

	errno_itoa = ft_itoa(g_exit_status);
	len = ft_strlen(errno_itoa);
	i = 0;
	while (i < len)
	{
		errno_value[i] = errno_itoa[i];
		i++;
	}
	errno_value[i] = '\0';
	free (errno_itoa);
	return (errno_value);
}

static char	*get_var_value(int i, int j, const char *str, t_shell *shell)
{
	char		*var_name;
	char		*var_value;

	var_value = NULL;
	var_name = calloc_sh(shell, sizeof(char) * j);
	ft_strlcpy(var_name, str + i + 1, j);
	if (str[i + 1] == QUESTION_MARK)
		var_value = get_errno_value();
	else
		var_value = get_env(shell, var_name);
	free(var_name);
	return (var_value);
}

// if $ + char spe except QUOTES
// if $ + number
// if $ + quote
int	is_not_a_var(char **str, const int i, int *move_i)
{
	*move_i = 0;
	if ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0')
		*move_i = 1;
	else if (ft_isdigit((*str)[i + 1]))
		ft_memmove(*str + i, *str + i + 2, strlen(*str + i) - 1);
	else if (is_quote((*str)[i + 1]))
		*move_i = 1;
	else if (is_other_spe_char_except_question_mark((*str)[i + 1]))
		*move_i = 2;
	else
		return (0);
	return (1);
}

void	move_j_to_end_of_var_name(char *str, const int i, int *j)
{
	if (str[i + 1] == QUESTION_MARK)
		*j = 2;
	else
	{
		*j = 1;
		while (is_word_char(str[i + *j]))
			*j += 1;
	}
}

//i starts at $
//echo + special chars that have a function are not to be handled by us
//per exemple $* or $# or () [] {} ...
//After this function i ends up on the next char that needs to be processed
//dst len = src_len + diff between var name and var value + 1 for \0

// ft_strlcpy(dst, *str, i + 1); copy str until $ to dst
// ft_strlcat(dst, value, dst_len); append var value
// ft_strlcat(dst, *str + i + j, dst_len); append rest of str
int	insert_var_in_str(char **str, const int i, t_shell *shell)
{
	int			j;
	int			dst_len;
	char		*dst;
	char		*value;

	if (is_not_a_var(str, i, &j))
		return (j);
	move_j_to_end_of_var_name(*str, i, &j);
	value = get_var_value(i, j, *str, shell);
	if (!value || *value == '\0')
	{
		ft_memmove(*str + i, *str + i + j, strlen(*str + i) - j + 1);
		return (0);
	}
	dst_len = ft_strlen(*str) - j + ft_strlen(value) + 1;
	dst = calloc_sh(shell, dst_len);
	ft_strlcpy(dst, *str, i + 1);
	ft_strlcat(dst, value, dst_len);
	ft_strlcat(dst, *str + i + j, dst_len);
	free_set_null((void **)str);
	*str = dst;
	return (ft_strlen(value));
}
