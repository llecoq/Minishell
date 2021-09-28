/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:39:23 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 15:11:42 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H
# define EVALUATOR_H

enum	e_execute
{
	PROMPT,
	STRING,
};

enum	e_process
{
	CHILD_PROCESS,
	PARENT_PROCESS,
	SINGLE_BUILTIN,
};

enum	e_redir
{
	FROM_FILE,
	FROM_STDIN,
	FROM_HEREDOC,
};

enum	e_file
{
	IS_VALID,
	IS_NOT_VALID,
	EXISTENT,
	NONEXISTENT = -1,
	AMBIGUOUS_REDIRECT = 4,
};

typedef struct s_redir
{
	char			*file_name;
	int				into_file;
	int				into_stdin;
	int				from_heredoc;
	int				from_file;
}				t_redir;

typedef struct s_file
{
	char			*file;
	char			*tmp;
	char			**argv;
	int				arg_type;
}				t_file;

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

typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

int		evaluator(t_shell *shell, t_cmd *cmds_list, int nb_of_cmds);
void	process_input(t_shell *shell, int flag);

int		execute_single_builtin_cmd(t_shell *shell, t_cmd *cmd, char **argv);
int		redir_single_builtin_cmd(char *cmd_name, char *argv);
int		find_builtin_function(char **argv, t_cmd *cmd);
int		last_child_status(pid_t last_child_pid);
int		path_is_unset(t_shell *shell, t_list **path_list);
int		path_is_not_absolute(char **argv, t_list **path_list);
int		ambiguous_redirect(t_cmd *cmd, char *file_name);
int		wexitstatus(int status);
void	create_pipe(t_shell *shell, t_cmd *cmd);
void	dup_input_redirection(t_shell *shell, t_cmd *cmd);
void	dup_output_redirection(t_shell *shell, t_cmd *cmd);
void	create_redirection(t_shell *shell, t_cmd *cmd, t_token *tk, int proc);
void	build_file_path(t_list **path_list, t_file *file, char ***argv);
void	execute_builtin_and_exit(t_shell *shell, t_cmd *cmd, char **argv);
void	execution_child_process(t_shell *shell, t_cmd *cmd);
char	*search_and_expand_file_name(t_shell *shell, t_cmd *cmd, t_token *tk);

#endif