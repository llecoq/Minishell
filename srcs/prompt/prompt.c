/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:54:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/28 15:46:49 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*format_and_add_colors(char *user, char *directory)
{
	char	*formated_line;
	char	*tmp;

	formated_line = ": ";
	formated_line = ft_strjoin(user, formated_line);
	tmp = formated_line;
	formated_line = ft_strjoin(BOLDMAGENTA, formated_line);
	free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, RESET);
	free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, BOLDWHITE);
	free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, directory);
	free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, RESET);
	free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, " ");
	free(tmp);
	return (formated_line);
}

static void	get_directory(char **directory, const char *path)
{
	while (*path)
		path++;
	while (*path != '/')
		path--;
	path++;
	*directory = (char *)path;
}

static void	get_user_dir(t_shell *shell)
{
	char	*user;
	char	*directory;
	char	*path;

	if (shell->user_dir)
		free_set_null((void **)&shell->user_dir);
	path = getcwd(NULL, 0);
	user = getenv("USER");
	get_directory(&directory, path);
	shell->user_dir = format_and_add_colors(user, directory);
	shell->change_directory = 0;
	free(path);
}

void	prompt(t_shell *shell)
{
	get_signal();
	if (shell->change_directory == 1)
		get_user_dir(shell);
	shell->input = readline(shell->user_dir);
	if (!shell->input)
	{
		shell->flush_stdin = TRUE;
		ft_exit(shell, NULL);
	}
	if (*shell->input)
		add_history(shell->input);
}
