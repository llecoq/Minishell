/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:14:46 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 16:41:52 by llecoq           ###   ########.fr       */
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
# include "prompt.h"
# include "evaluator.h"
# include "builtin.h"
# include "utils.h"

int						g_exit_status;

typedef int				t_flag;
typedef struct s_shell	t_shell;

typedef struct s_token
{
	char			*word;
	t_flag			cmd;
	t_flag			arg;
	t_flag			redir;
	struct s_token	*next;
	struct s_token	*previous;
}						t_token;

//last cmd_array is set to NULL;
typedef struct s_shell
{
	char			*input;
	char			*user_dir;
	char			**envp;
	const char		***cmd_argv;
	t_cmd			*cmds_list;
	t_list			*env_list;
	t_list			*split_cmds_by_semicolons;
	t_list			*export_list;
	t_list			*path;
	t_token			**cmd_array;
	int				change_directory;
	int				nb_of_cmds;
	int				execute_minishell_from_str;
	int				flush_stdin;
	int				child_process;
}						t_shell;

enum	e_redirections
{
	PIPE = 4,
	TRUNC = 5,
	APPEND = 6,
	HEREDOC = 7,
	STOP_VALUE = 8,
	INPUT_REDIR = 9,
};

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
	SINGLE_QUOTE = 39,
	DOUBLE_QUOTE = 34,
};

enum	e_errors
{
	SYSCALL_ERROR = 0,
	NO_CLOSING_QUOTE = -1,
	INVALID_ARGS_OR_OPTIONS = 2,
	NOTHING_AFTER_REDIR = -2,
	NOTHING_BEFORE_REDIR = 258,
	REDIR_ISNT_1_WORD = -3,
	CMD_IS_WRONG = -4,
	CANT_OPEN_FILE = -5,
	CMD_NOT_FOUND = 127,
	FILE_IS_DIR = -7,
	FAILED = -1,
};

enum	e_word_chars
{
	FIRST_LETTER = 1,
	OTHER_LETTERS = 2,
};

/*
 ** char_detection.c  
 */

int			is_redirection(const char *str, int i);
int			is_quote(const char c);
int			finished_by_spaces(const char *str);
int			is_word_char(int c);
int			is_other_spe_char_except_question_mark(char c);

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
void		print_argv(t_cmd *cmd_list);

/*
** token_list_functions2.c  
*/

void		add_tokens_to_list(t_shell *shell, t_token *head, char	**word);

/*
** ------------------------------------------------------------------ UTILS
*/

/*
** parsing
*/

void		store_environment(t_shell *shell, char *const *envp);
void		store_environment_tab(t_shell *shell, t_list *env_list, int len);
void		tokenize(t_shell *shell, const char *input);
void		parse(t_shell *shell);
char		*process_variables(char *token, t_shell *shell);

/*
** parser_utils
*/

void		turn_on_flag(int flag, t_token *cpy);
void		erase_current_cmd(t_token **cmd_array, int i, t_shell *shell);
void		create_empty_cmds_list(t_shell *shell, int nb_of_cmds);
void		create_heredoc(t_shell *shell, t_token **cmd_array, \
t_cmd *cmds_list);
int			insert_home_directory_in_str(t_shell *shell, char **str);
int			process_tilde(t_shell *shell, int *i, char **tk_cpy);
int			dollar_sign_followed_by_quote(char *tk_cpy, const int i);

/*
** parser_flags
*/

void		set_flag_after_redirection(t_token **cmd_array, char **error_str);
void		set_redir_arg_flags(t_token **cmd_array);

/*
** parser_variables
*/

void		arg_syntax_processing(t_token **cmd_array, t_shell *shell);
void		replace_token_with_var(char **token, t_shell *shell);

/*
** parser_variables_expansions.c
*/

int			insert_var_in_str(char **str, const int i, t_shell *shell);

/*
** parser_split_semicolon
*/

t_list		*split_by_semicolons(t_shell *shell, char *input);

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
** tokenizer_utils
*/

int			count_commands(const char *input);

/*
** ---------------------------------------------------------------- PARSING
*/

#endif
