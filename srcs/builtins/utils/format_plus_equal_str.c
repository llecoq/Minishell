/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_plus_equal_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 15:43:09 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 14:44:10 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_variable(t_shell *shell, char **string, int len)
{
	int		i;
	char	*dst;

	i = 0;
	dst = calloc_sh(shell, len);
	while ((*string)[i] != '+')
	{
		dst[i] = (*string)[i];
		i++;
	}
	while (i < len - 1)
	{
		dst[i] = (*string)[i + 1];
		i++;
	}
	(*string) = dst;
}

void	append_value_to_var(t_shell *shell, char **string, char *var, int len)
{
	char	*str_cpy;
	int		i;
	int		dst_len;
	int		var_len;

	str_cpy = ft_strdup(*string);
	i = 0;
	while ((*string)[i] != '=')
		i++;
	var_len = ft_strlen(var);
	dst_len = var_len + len - i;
	(*string) = calloc_sh(shell, dst_len);
	ft_memmove((*string), var, var_len);
	while (len > i + 1)
	{
		(*string)[dst_len - 2] = str_cpy[len - 1];
		len--;
		dst_len--;
	}
	free_set_null((void **)&str_cpy);
}

void	format_plus_equal_string(t_shell *shell, char **string, char *var)
{
	int		len;

	len = ft_strlen(*string);
	if (var == NULL)
		add_new_variable(shell, string, len);
	else if (var)
		append_value_to_var(shell, string, var, len);
}
