/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_value_to_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 11:30:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/15 16:20:10 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_name(t_shell *shell, char **name, char *string)
{
	int	i;

	i = 0;
	while (string[i] && string[i] != '+')
		i++;
	i++;
	*name = calloc_sh(shell, i);
	ft_strlcpy(*name, string, i);
}

static int	string_value_is_null(char *string)
{
	while (*string && *string != '=')
		string++;
	if (*string)
		string++;
	if (*string == 0)
		return (1);
	return (0);
}

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
		ft_lstadd_back(&list, ft_lstnew(string));
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
