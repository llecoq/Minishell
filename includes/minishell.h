/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 11:36:25 by abonnel          ###   ########.fr       */
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

typedef struct 	s_token
{
	char			*word;
	struct s_token	*next;
}				t_token;

typedef struct	s_path
{
	char			*path;
	struct s_token	*next;
}				t_path;

typedef struct	s_shell
{
	char	*input; // readline
	t_token **s_cmd_array;
	t_path	*path;
}				t_shell;

int main();
void	hihi(void);

#endif
