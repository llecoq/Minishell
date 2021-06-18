/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/18 10:34:17 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

typedef struct 	s_token
{
	char			*word;
	struct s_token	*previous;
	struct s_token	*next;
}				t_token;

typedef struct	s_path
{
	struct s_token	*previous;
	struct s_token	*next;
}				t_path;


typedef struct	s_shell
{
	char	*input; // readline
	t_token **s_cmd_array;
	t_path
}				t_shell;

#endif
