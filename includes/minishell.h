/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 16:28:53 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/errno.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct 	s_token
{
	char			*word;
	struct s_token	*next;
}				t_token;

typedef struct	s_shell
{
	char	*input; // readline
	char	**env;
	t_token **cmd_array; //last index is set to NULL;
	t_list	*path;
}				t_shell;

typedef int t_bool;

/*
** utils
*/

void		*calloc_sh(t_shell *shell, int size);
void		prompt(t_shell *shell);
void		del(void *content);
void		clear_memory(t_shell *shell);
void		error_quit(t_shell *shell, int error_type);
void		error(t_shell *shell, int error_type);

/*
** parsing
*/

int			store_environment(t_shell *shell, char **env);
int			store_environment_tab(t_shell *shell, t_list *path, int len);
t_token 	**tokenize(t_shell *shell, char **input);

#endif
