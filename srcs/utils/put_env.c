/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 10:30:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/01 13:08:10 by llecoq           ###   ########.fr       */
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
int	valid_var_name(t_shell *shell, char *string, char **name)
{
	int	i;

	if (ft_isdigit(string[0]))
		return (0);		// if first character is digit, export: not an identifier: $name
	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] != '=')
		return (-1);		// only visible in export, but not in env
	i++;
	*name = calloc_sh(shell, i);
	ft_strlcpy(*name, string, i);
	return (1);
}

int	found_var(t_list *env_list, char *name, t_list **variable_ptr, size_t len)
{
	char	*content;

	while (env_list)
	{
		content = (char *)env_list->content;
		if (ft_strncmp(content, name, len) == 0 && content[len] == '=')
		{
			free(env_list->content);
			*variable_ptr = env_list;
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

int	put_env(t_shell *shell, char *string)
{
	size_t	len;
	t_list	*variable_ptr;
	char	*name;
	int		return_value;

	if (!string)
		return (-1);
	return_value = valid_var_name(shell, string, &name);
	if (return_value == 1)
	{
		len = ft_strlen(name);
		if (found_var(shell->env_list, name, &variable_ptr, len))
		{
			variable_ptr->content = ft_strdup(string);
			variable_ptr->variable = IS_SET;
		}
		else
			ft_lstadd_back(&shell->env_list, ft_lstnew(ft_strdup(string)));
		free(name);
		store_environment_tab(shell, shell->env_list, env_size(shell->env_list));
	}
	return (return_value); // error code
}
