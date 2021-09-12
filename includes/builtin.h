/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:48:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/12 19:02:38 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

enum	e_export
{
	EXPORT_LIST,
	ENV_LIST,
	ADDED_TO_EXPORT_LIST = 4,
};

enum	e_builtins
{
	CD,
	ENV,
	PWD,
	UNSET,
	EXPORT,
};

enum	e_put_env
{
	IS_SET = 1,
	IS_UNSET = 0,
	APPEND_VALUE = 6,
	IS_A_DIRECTORY = 126,
	IS_NOT_A_DIRECTORY = 0,
	NOT_A_VALID_IDENTIFIER = 1,
	FILENAME_ARGUMENT_REQUIRED = 2,
};

typedef struct s_shell	t_shell;
typedef struct s_list	t_list;

int		ft_exit(t_shell *shell, char **argv);
int		ft_echo(t_shell *shell, char **argv);
int		ft_cd(t_shell *shell, char **argv);
int		ft_pwd(t_shell *shell, char **argv);
int		ft_export(t_shell *shell, char **argv);
int		ft_unset(t_shell *shell, char **argv);
int		ft_env(t_shell *shell, char **argv);
int		found_var(t_list *env_list, char *name, t_list **variable_ptr, \
size_t len);
int		process_value_to_append(t_shell *shell, char *string, char **name);
void	format_plus_equal_string(t_shell *shell, char **string, char *var);
void	store_list(t_list **list, char *const *env);

#endif