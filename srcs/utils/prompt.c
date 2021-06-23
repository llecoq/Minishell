/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:54:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/23 12:12:23 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_and_add_colors(char *user, char *directory)
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

void	get_path(char **directory, const char *path)
{
	while (*path)
		path++;
	while (*path != '/')
		path--;
	path++;
	*directory = (char *)path;
}

void	get_user_dir(t_shell *shell)
{
	char	*user;
	char	*directory;
	char	*path;

	if (shell->user_dir)
		free_set_null((void **)&shell->user_dir);
	path = NULL;
	user = getenv("USER");
	path = getcwd(NULL, 0);
	get_path(&directory, path);
	shell->user_dir = format_and_add_colors(user, directory);
	shell->change_directory = 0;
	free(path);
}

void	prompt(t_shell *shell)
{
	if (shell->change_directory == 1)
		get_user_dir(shell);
	shell->input = readline(shell->user_dir);
	signal(SIGINT, sig_handler);
	if (*shell->input)
		add_history(shell->input);
	// signal(SIGINT, sig_handler);
	// gerer l'history pour ne pas qu'il ecrase le user et path
}
