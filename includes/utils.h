/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:14:34 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/24 15:59:24 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

enum	e_split_token
{
	IS_SINGLE,
	IS_MULTIPLE,
	TILDE = 126,
	QUESTION_MARK = 63,
	UNDERSCORE = 95,
	SEMICOLON = 59,
};

typedef struct s_shell	t_shell;
typedef struct s_list	t_list;
typedef struct s_token	t_token;

void		*calloc_sh(t_shell *shell, int size);
void		del(void *content);
void		clear_memory(t_shell *shell);
void		clear_nonessential_memory(t_shell *shell);
void		free_cmd_array(t_token **cmd_array);
void		error_quit(t_shell *shell, int error_type, char *str);
void		err_clear(t_shell *shell, int error_type, char *str);
void		error(t_shell *shell, int error_type, char *str);
char		*create_error_str(char *next_token);
void		print_list(t_list *list);
void		print_env(t_shell *shell, int fd);
void		sort_alphabetically_list(t_list **export_list);
void		split_multiple_words_into_tokens(t_shell *shell);
void		free_split_cmds_by_semicolons(t_shell *shell);
char		*get_env(t_shell *shell, const char *name);
char		*join_args(char	**argv, char *flag);
int			put_env(t_shell *shell, char *string);
int			invalid_args_or_options(char **argv, char *name, int builtin_type);
int			valid_name(char *argv, char *built_name);
size_t		env_size(t_list *env_list);

#endif