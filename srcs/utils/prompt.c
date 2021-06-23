/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:54:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/06/23 10:32:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        // printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

char	*format_and_add_colors(char *user, char *directory)
{
	char	*formated_line;
	char	*tmp;

	formated_line = ": ";
	formated_line = ft_strjoin(user, formated_line);
	tmp = formated_line;
	// formated_line = ft_strjoin(BOLDMAGENTA, formated_line);
	// free(tmp);
	// tmp = formated_line;
	// formated_line = ft_strjoin(formated_line, RESET);
	// free(tmp);
	// tmp = formated_line;
	// formated_line = ft_strjoin(formated_line, BOLDWHITE);
	// free(tmp);
	tmp = formated_line;
	formated_line = ft_strjoin(formated_line, directory);
	free(tmp);
	// tmp = formated_line;
	// formated_line = ft_strjoin(formated_line, RESET);
	// free(tmp);
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

char	*get_user_dir(void)
{
	char	*user;
	char	*directory;
	char	*path;
	char	*user_dir;

	path = NULL;
	user = getenv("USER");
	path = getcwd(NULL, 0);
	get_path(&directory, path);
	user_dir = format_and_add_colors(user, directory);
	free(path);
	return (user_dir);
}

void	prompt(t_shell *shell)
{
	char	*user_dir;
	
	user_dir = get_user_dir();
	shell->input = readline(user_dir);
	if (*shell->input)
		add_history(shell->input);
	// signal(SIGINT, sig_handler);
	free(shell->input);
	free(user_dir);
	// gerer l'history pour ne pas qu'il ecrase le user et path
}
