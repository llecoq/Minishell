/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 14:44:04 by abonnel          ###   ########.fr       */
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
	t_token **cmd_array;
	t_list	*path;
}				t_shell;

typedef int t_bool;

void		prompt(t_shell *shell);
t_token 	**tokenize(t_shell *shell, char **input);

#endif
