/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_value_to_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:30:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/09 13:43:24 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_name(t_shell *shell, char **name, char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '+')
		i++;
	i++;
	*name = calloc_sh(shell, i);
	ft_strlcpy(*name, string, i);
}

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
	ft_memmove((*string), var, len);
	while (len > i + 1)
	{
		(*string)[dst_len - 2] = str_cpy[len - 1];
		len--;
		dst_len--;
	}
	free_set_null((void **)&str_cpy);
}

void	format_plus_equal_string(t_shell *shell, char **string, char *variable)
{
	int		len;

	len = ft_strlen(*string);
	if (variable == NULL)
		add_new_variable(shell, string, len);
	else if (variable)
		append_value_to_var(shell, string, variable, len);
}

int	string_value_is_null(char *string)
{
	while (*string && *string != '=')
		string++;
	if (*string)
		string++;
	if (*string == 0)
		return (1);
	return (0);
}

// leaks string ?
void	append_into_list(t_shell *shell, char *string, char **name, int type)
{
	size_t	len;
	t_list	*list;
	t_list	*variable_ptr;

	list = NULL;
	if (type == EXPORT_LIST)
		list = shell->export_list;
	else if (type == ENV_LIST)
		list = shell->env_list;
	len = ft_strlen(*name);
	if (found_var(list, *name, &variable_ptr, len))
	{
		if (string_value_is_null(string))
			return ;
		format_plus_equal_string(shell, &string, variable_ptr->content);
		free(variable_ptr->content);
		variable_ptr->content = string;
		variable_ptr->variable = IS_SET;
	}
	else
	{
		format_plus_equal_string(shell, &string, NULL);
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(string)));
	}
}

int	process_value_to_append(t_shell *shell, char *string, char **name)
{
	find_name(shell, name, string);
	append_into_list(shell, string, name, ENV_LIST);
	append_into_list(shell, string, name, EXPORT_LIST);
	free(*name);
	store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
	sort_alphabetically_list(&shell->export_list);
	return (APPEND_VALUE);
}
