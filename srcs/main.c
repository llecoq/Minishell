/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/26 20:49:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shell_var_to_null(t_shell *shell)
{
	shell->change_directory = 1;
	shell->user_dir = NULL;
	shell->input = NULL;
	shell->envp = NULL;
	shell->env_list = NULL;
	shell->path = NULL;
	shell->cmd_array = NULL;
	exit_status = 0;
}

int	count_cmds(char *input, int *nb_of_cmds)
{
	int		i;
	char	closing_quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == QUOTE || input[i] == DOUBLE_QUOTE)
		{
			closing_quote = input[i];
			i++;
			while (input[i] && input[i] != closing_quote)
				i++;
			if (input[i] == closing_quote)
				i++;
		}
		if (input[i] == SEMICOLON && input[i + 1])
			*nb_of_cmds += 1;
		if (input[i])
			i++;
	}
	return (*nb_of_cmds);
}

char	*fill_split_with_cmd(t_shell *shell, char *input, int i, int j)
{
	char	*split_cmd;
	
	split_cmd = calloc_sh(shell, sizeof(char) * (j - i + 1));
	j--;
	while (j >= i)
	{
		split_cmd[j - i] = input[j];
		j--;
	}
	return (split_cmd);
}

void	find_cmd_line(char *input, int *i)
{
	char	closing_quote;

	while (input[*i])
	{
		if (input[*i] == QUOTE || input[*i] == DOUBLE_QUOTE)
		{
			(*i)++;
			closing_quote = input[*i];
			while (input[*i] && input[*i] != closing_quote)
				(*i)++;
			if (input[*i] == closing_quote)
				(*i)++;
		}
		if (input[*i] == SEMICOLON)
		{
			(*i)++;
			return ;
		}
		(*i)++;
	}
}

char	**split_by_semicolons(t_shell *shell, char *input)
{
	int		i;
	int		j;
	int		nb_of_cmds;
	int		cmd_nb;
	char	**split_cmds;

	cmd_nb = 0;
	nb_of_cmds = 1;
	split_cmds = NULL;
	count_cmds(input, &nb_of_cmds);
	split_cmds = calloc_sh(shell, sizeof(char *) * (nb_of_cmds + 1));
	i = 0;
	j = 0;
	while (nb_of_cmds > 0)
	{
		find_cmd_line(input, &j);
		split_cmds[cmd_nb] = fill_split_with_cmd(shell, input, i, j);
		i = j + 1;
		if (input[j])
			j++;
		nb_of_cmds--;
		cmd_nb++;
	}
	return (split_cmds);
}

void	print_char_tab(char **char_tab)
{
	int	i;

	i = 0;
	while (char_tab[i])
	{
		ft_printf(STDOUT_FILENO, "%s\n", char_tab[i]);
		i++;	
	}
}

static void process_input(t_shell *shell, int flag)
{		
	int		i;
	char	**split_cmds;
	
	split_cmds = split_by_semicolons(shell, shell->input);
	if (flag == PROMPT)
		free_set_null((void **)&shell->input);
	// print_char_tab(split_cmds);
	i = 0;
	while (split_cmds[i])
	{
		tokenize(shell, split_cmds[i]);
		free_set_null((void **)&split_cmds[i]);
		if (shell->cmd_array == NULL)
			return ;
		parse(shell);
		if (&shell->cmd_array[0])
			exit_status = evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
		clear_nonessential_memory(shell);
		i++;
	}
	free_split(split_cmds);
}

void	execute_minishell_script(t_shell *shell, char **argv, char **envp)
{
	int		fd;
	int		ret;

	fd = open(argv[1], O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &shell->input);
		if (ret <= 0)
			ft_exit(shell, NULL);
		store_environment(shell, envp);
		tokenize(shell, shell->input);
		if (shell->cmd_array == NULL) //in case of missing closing bracket / empty input
			return ;
		parse(shell);
		if (&shell->cmd_array[0])
			exit_status = evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
		clear_nonessential_memory(shell);
	}
	clear_memory(shell);
}

void	execute_minishell_from_string(t_shell *shell, char *arg, char **envp)
{
	shell->input = arg;
	store_environment(shell, envp);
	process_input(shell, STRING);
	// tokenize(shell, shell->input);
	// if (shell->cmd_array == NULL) //in case of missing closing bracket / empty input
	// 	return ;
	// parse(shell);
	// if (&shell->cmd_array[0] != NULL)
	// 	exit_status = evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
	ft_exit(shell, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	set_shell_var_to_null(&shell);
	if (argc == 1)
	{
		store_environment(&shell, envp);
		while (1)
		{
			prompt(&shell);
			process_input(&shell, PROMPT);
		}
	}
	else if (argc == 2 && ft_strncmp(argv[1], "./", 2) == 0)
		execute_minishell_script(&shell, argv, envp);
	else if (argc >= 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		execute_minishell_from_string(&shell, argv[2], envp);
	else
		ft_printf(2, "minishell: Wrong use. Try again !\n"); // quel exit number ?
	clear_memory(&shell);
	return (exit_status);
}
