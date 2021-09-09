/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 10:30:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/09 14:48:58 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

    //    The putenv() function adds or changes the value of environment
    //    variables.  The argument string is of the form name=value.  If
    //    name does not already exist in the environment, then string is
    //    added to the environment.  If name does exist, then the value of
    //    name in the environment is changed to value.  The string pointed
    //    to by string becomes part of the environment, so altering the
    //    string changes the environment.

	// The putenv() function returns zero on success.  On failure, it
	// returns a nonzero value, and errno is set to indicate the error.

// EXPORTED VAR ARE RANDOMLY ADDED INSIDE THE ENV, WHAT'S THE LOGIC ?
// Our fonction just add them at the end of the list so far

int	found_var(t_list *env_list, char *name, t_list **variable_ptr, size_t len)
{
	char	*content;

	while (env_list)
	{
		content = (char *)env_list->content;
		if (ft_strncmp(content, name, len) == 0)
		{
			if (content[len] == '=')
			{
				*variable_ptr = env_list;
				return (1);
			}
			// else if (ft_strncmp(content, "OLDPWD", 6) == 0
			// 	&& content[6] == 0)
			// {
			// 	env_list->variable = IS_UNSET;
			// 	return (0);
			// }
		}
		env_list = env_list->next;
	}
	return (0);
}

int	plus_equal_operator(char *string, int i)
{
	char	*ptr;

	ptr = &string[i];
	if (i > 0)
		ptr--;
	if (ft_strncmp(ptr, "+=", 2) == 0)
		return (1);
	return (0);
}

void	insert_into_list(t_shell *shell, char *string, char *name, int type)
{
	size_t	len;
	t_list	*list;
	t_list	*variable_ptr;

	list = NULL;
	if (type == EXPORT_LIST)
		list = shell->export_list;
	else if (type == ENV_LIST)
		list = shell->env_list;
	len = ft_strlen(name);
	if (found_var(list, name, &variable_ptr, len))
	{
		free(variable_ptr->content);
		variable_ptr->content = ft_strdup(string);
		variable_ptr->variable = IS_SET;
		if (ft_strncmp(name, "PATH", 5) == 0)
			shell->path->variable = IS_SET;
	}
	else
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(string)));
}

// int	process_value_to_append(t_shell *shell, char *string, char **name)
// {
// 	size_t	len;
// 	t_list	*list;
// 	t_list	*variable_ptr;

// 	// list = shell->env_list;
// 	find_name(shell, name, string);
// 	len = ft_strlen(*name);
// 	if (found_var(shell->env_list, *name, &variable_ptr, len))
// 	{
// 		format_plus_equal_string(shell, &string, variable_ptr->content);
// 		free(variable_ptr->content);
// 		variable_ptr->content = string;
// 		variable_ptr->variable = IS_SET;
// 	}
// 	else
// 	{
// 		format_plus_equal_string(shell, &string, NULL);
// 		ft_lstadd_back(&shell->env_list, ft_lstnew(string));
// 		// ft_lstadd_back(&shell->export_list, ft_lstnew(strdup(string)));
// 	}
// 	free(*name);
// 	store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
// 	sort_alphabetically_list(&shell->export_list);
// 	return (APPEND_VALUE);
// }

int	valid_var_name(t_shell *shell, char *string, char **name)
{
	int		i;
	t_list	*new_elem;

	if (ft_isdigit(string[0]))
		return (NOT_A_VALID_IDENTIFIER);		// if first character is digit, export: not an identifier: $name
	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (plus_equal_operator(string, i))
		return (process_value_to_append(shell, string, name));
	if (string[i] != '=')
	{
		new_elem = ft_lstnew(ft_strdup(string));
		new_elem->variable = IS_SET;
		ft_lstadd_back(&shell->export_list, new_elem);
		sort_alphabetically_list(&shell->export_list);
		return (ADDED_TO_EXPORT_LIST);		// only visible in export, but not in env
	}
	i++;
	*name = calloc_sh(shell, i);
	ft_strlcpy(*name, string, i);
	return (IS_VALID);
}


int	put_env(t_shell *shell, char *string)
{
	char	*name;
	int		return_value;

	if (!string) // quelle valeur retourner ?
		return (-1);
	if (string[0] == '=')
	{
		ft_printf(2, "minishell: `%s': not a valid identifier\n", string);
		return (NOT_A_VALID_IDENTIFIER);
	}
	return_value = valid_var_name(shell, string, &name);
	if (return_value == IS_VALID)
	{
		insert_into_list(shell, string, name, ENV_LIST);
		insert_into_list(shell, string, name, EXPORT_LIST);
		free(name);
		store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
		sort_alphabetically_list(&shell->export_list);
	}
	if (return_value == ADDED_TO_EXPORT_LIST)
		return_value = IS_VALID;
	return (return_value); // error code
}
