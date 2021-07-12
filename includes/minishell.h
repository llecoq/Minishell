/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/12 16:42:07 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "readline/8.1/include/readline/readline.h"
# include "readline/8.1/include/readline/history.h"
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <term.h>
# include <curses.h>
# include <errno.h>
# include "../libft/libft.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

typedef int t_bool;
typedef int t_flag;

typedef struct 	s_token
{
	char			*word;
	t_flag			cmd;
	t_flag			arg;
	t_flag			redir;
	char			*cmd_path;
	struct s_token	*next;
}				t_token;

typedef struct	s_shell
{
	char		*input; // readline
	char		*user_dir;
	char		**envp;
	const char	***cmd_argv;
	t_list		*env_list;
	t_list		*export_list;
	t_list		*path;
	t_token 	**cmd_array; //last cmd_array is set to NULL;
	int			change_directory;
	int			exit_code;
}				t_shell;

enum	e_redirections
{
	PIPE = 1,
	REDIR = 2,
	APPEND = 3,
	INREDIR = 4,
	HEREDOC = 5,
};

//REDIR = 2 already exists
enum	e_flags
{
	CMD = 1,
	ARG = 3,
};

enum	e_quotes
{
	SINGLE_QUOTE = 1,
	DBLE_QUOTE = 2,
};

enum	e_errors
{
	NO_CLOSING_QUOTE = -1,
	NOTHING_AFTER_REDIR = -2,
	REDIR_IS_NOT_ONE_WORD,
};

enum	e_env
{
	IS_SET = 1,
	IS_UNSET = 0,
	ILLEGAL_OPTION = 2,
	PERMISSION_DENIED = 3,
	NO_SUCH_FILE_OR_DIRECTORY = 4,
};

enum	e_builtins
{
	BUILT_CD = 1,
	BUILT_PWD = 2,
	BUILT_ENV = 3,
	BUILT_ECHO = 4,
	BUILT_EXIT = 5,
	BUILT_UNSET = 6,
	BUILT_EXPORT = 7,
};

/*
** UTILS ----------------------------------------------------------------
*/

void		*calloc_sh(t_shell *shell, int size);
void		prompt(t_shell *shell);
void		del(void *content);
void		clear_memory(t_shell *shell);
void		clear_nonessential_memory(t_shell *shell);
void		free_cmd_array(t_token **cmd_array);
void		error_quit(t_shell *shell, int error_type);
void		error(t_shell *shell, int error_type, char *str);
void		sig_handler(int signum);
void		get_signal(void);
void		print_list(t_list *list);
void		print_env(t_shell *shell);
void		sort_alphabetically_list(t_list **export_list);
char		*get_env(t_shell *shell, const char *name);
int			put_env(t_shell *shell, char *string);
int			invalid_args_or_options(char **argv, char *name);
int			valid_name(char *argv, char *built_name);
size_t		env_size(t_list *env_list);

/*
 ** char_detection.c  
 */

int			is_redirection(const char *str, int i);
int			is_quote(const char c);
int			finished_by_spaces(const char *str);

/*
** token_list_functions.c  
*/

t_token		*return_tail_token(t_token *token_lst);
void		add_token_tail(t_token **head, t_token *new_token);
t_token		*create_new_token(char *token, t_shell *shell);
void		print_cmd_array(t_token **cmd_array, int flags);

/*
** ---------------------------------------------------------------- UTILS
*/

/*
** parsing
*/

int			store_environment(t_shell *shell, char *const *envp);
void   		store_environment_tab(t_shell *shell, t_list *env_list, int len);
void		tokenize(t_shell *shell, const char *input);
void		parse(t_shell *shell);
char		*process_variables(char *str, t_shell *shell);


/*
** builtins
*/

int	ft_exit(t_shell *shell, char **argv);
int	ft_echo(t_shell *shell, char **argv);
int	ft_cd(t_shell *shell, char **argv);
int	ft_pwd(t_shell *shell, char **argv);
int	ft_export(t_shell *shell, char **argv);
int	ft_unset(t_shell *shell, char **argv);
int	ft_env(t_shell *shell, char **argv);

#endif
