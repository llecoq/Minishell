/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/19 13:22:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "enum.h"

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

// int	global_errno;

typedef int 	t_bool;
typedef int 	t_flag;
typedef struct 	s_shell t_shell;

typedef struct s_redir
{
	int				into_file;
	int				into_stdin;
	int				from_heredoc;
	int				from_file;
}				t_redir;

typedef struct s_cmd
{
	char			**argv;
	int				(*ft_builtin)(t_shell *, char **);
	int				pipefd[2];
	struct s_redir	redir;
	struct s_token	*token_list;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

typedef struct 	s_token
{
	char			*word;
	t_flag			cmd;
	t_flag			arg;
	t_flag			redir;
	t_flag			error;
	// int				fd;										//delete
	// int				(*ft_builtin)(t_shell *, char **);		//delete
	// char			*cmd_path;								//delete
	// char			**argv;									//delete
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;

typedef struct s_file
{
	char			*file;
	char			*tmp;
	char			**argv;
	int				arg_type;
}				t_file;

typedef struct	s_shell
{
	char			*input; // readline
	char			*user_dir;
	char			**envp;
	const char		***cmd_argv;
	t_cmd			*cmds_list;
	t_list			*env_list;
	t_list			*export_list;
	t_list			*path;
	t_token 		**cmd_array; //last cmd_array is set to NULL;
	int				change_directory;
	int				nb_of_cmds;
}				t_shell;

enum	e_redirections
{
	PIPE = 4,
	TRUNC = 5,
	APPEND = 6,
	HEREDOC = 7,
	STOP_VALUE = 8,
	INPUT_REDIR = 9,
};

//REDIR = 2 already exists
enum	e_flags
{
	ARG = 0,
	CMD = 1,
	IS_REDIR = 2,
	IS_FILE = 3,
	IS_PATH = 4,
};

enum	e_quotes
{
	SINGLE_QUOTE = 1,
	DBLE_QUOTE = 2,
};

enum	e_errors
{
	SYSCALL_ERROR = 0,
	NO_CLOSING_QUOTE = -1,
	NOTHING_AFTER_REDIR = -2,
	REDIR_ISNT_1_WORD = -3,
	CMD_IS_WRONG = -4,
	CANT_OPEN_FILE = -5,
	CMD_NOT_FOUND = 127,
	FILE_IS_DIR = -7,
	FAILED = -8,
};

enum	e_word_chars
{
	FIRST_LETTER = 1,
	OTHER_LETTERS = 2,
};

enum	e_split_token
{
	IS_SINGLE,
	IS_MULTIPLE,
	DOUBLE_QUOTE = 34,
	QUOTE = 39,
};

enum	e_env
{
	IS_SET = 1,
	IS_UNSET = 0,
	ILLEGAL_OPTION = 2,
	PERMISSION_DENIED = 3,
	ADDED_TO_EXPORT_LIST = 4,
	NOT_A_VALID_IDENTIFIER = 1,
	NO_SUCH_FILE_OR_DIRECTORY = 5,
};

/*
** EVALUATOR ------------------------------------------------------------
*/
int	evaluator(t_shell *shell, t_cmd *cmds_list, int nb_of_cmds);
void	create_pipe(t_shell *shell, t_cmd *cmd);
int	last_child_status(pid_t last_child_pid);
void	dup_input_redirection(t_shell *shell, t_cmd *cmd);
void	dup_output_redirection(t_shell *shell, t_cmd *cmd);
void	create_redirection(t_shell *shell, t_cmd *cmd, t_token *token);
int	path_is_unset(t_shell *shell, t_list **path_list);
int	path_is_not_absolute(char **argv, t_list **path_list);
void	build_file_path(t_list **path_list, t_file *file, char ***argv);
// int	cmd_is_builtin(t_cmd *cmd, int **ft_builtin);
// void	execute_builtin_and_exit(t_shell *shell, t_cmd *cmd, char **argv);
int	find_builtin_function(char *cmd_name, t_cmd *cmd);

//PARSING
void	create_empty_cmds_list(t_shell *shell, int nb_of_cmds);
void	create_heredoc(t_shell *shell, t_token **cmd_array, t_cmd *cmds_list);


/*
** ------------------------------------------------------------ EVALUATOR
*/

/*
** UTILS ----------------------------------------------------------------
*/

void		*calloc_sh(t_shell *shell, int size);
void		prompt(t_shell *shell);
void		del(void *content);
void		clear_memory(t_shell *shell);
void		clear_nonessential_memory(t_shell *shell);
void		free_cmd_array(t_token **cmd_array);
void		error_quit(t_shell *shell, int error_type, char *str);
void		err_clear(t_shell *shell, int error_type, char *str);
void		error(t_shell *shell, int error_type, char *str);
void		sig_handler(int signum);
void		get_signal(void);
void		print_list(t_list *list);
void		print_env(t_shell *shell);
void		sort_alphabetically_list(t_list **export_list);
void		split_multiple_words_into_tokens(t_shell *shell);
char		*get_env(t_shell *shell, const char *name);
char		*join_args(char	**argv, char *flag);
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
int			is_word_char(int c, int mode);
int			is_word(const char *str);

/*
** token_list_functions.c  
*/

t_token		*return_tail_token(t_token *token_lst);
void		add_token_tail(t_token **head, t_token *new_token);
t_token		*create_new_token(char *token, t_shell *shell);
void		print_cmd_array(t_token **cmd_array, int flags);
void		reset_previous_pointers(t_token *head);
void		erase_token(t_token **token, t_token **head, t_shell *shell);
void		erase_cmd(t_token *cmd);
// void		print_argv(t_token **cmd_array);
void		print_argv(t_cmd *cmd_list);



/*
** ------------------------------------------------------------------ UTILS
*/

/*
** PARSING ----------------------------------------------------------------
*/

/*
** parsing
*/

void		store_environment(t_shell *shell, char *const *envp);
void   		store_environment_tab(t_shell *shell, t_list *env_list, int len);
void		tokenize(t_shell *shell, const char *input);
void		parse(t_shell *shell);
char		*process_variables(char *token, t_shell *shell);

/*
** parser_utils
*/

void		turn_on_flag(int flag, t_token *cpy);
void		erase_current_cmd(t_token **cmd_array, int i, t_shell *shell);

/*
** parser_flags
*/

void		set_flag_after_redirection(t_token **cmd_array, char **error_str);
void		set_redir_arg_flags(t_token **cmd_array);

/*
** parser_variables
*/

void 		arg_syntax_processing(t_token **cmd_array, t_shell *shell);
void		replace_token_with_var(char **token, t_shell *shell);

/*
** parser_redirection
*/

void		check_and_create_redirections(t_token **cmd_array, t_shell *shell);

/*
** parser_trim_quotes
*/

void		remove_quotes(t_token **cmd_array, t_shell *shell);

/*
** parser_find_command
*/

void		find_command(t_token **cmd_array, t_shell *shell);

/*
** parser_arg_list
*/

void		create_argument_list(t_token **cmd_array, t_shell *shell);

/*
** ---------------------------------------------------------------- PARSING
*/

/*
** builtins
*/

int			ft_exit(t_shell *shell, char **argv);
int			ft_echo(t_shell *shell, char **argv);
int			ft_cd(t_shell *shell, char **argv);
int			ft_pwd(t_shell *shell, char **argv);
int			ft_export(t_shell *shell, char **argv);
int			ft_unset(t_shell *shell, char **argv);
int			ft_env(t_shell *shell, char **argv);

#endif
