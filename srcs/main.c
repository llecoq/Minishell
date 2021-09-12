/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:47:25 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/12 15:45:53 by llecoq           ###   ########.fr       */
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

char	*fill_command_line(t_shell *shell, char *input, int start, int end)
{
	char	*split_cmd;
	
	split_cmd = calloc_sh(shell, sizeof(char) * (end - start + 1));
	end--;
	while (end >= start)
	{
		split_cmd[end - start] = input[end];
		end--;
	}
	return (split_cmd);
}


void	find_command_line(char *input, int *i)
{
	char	closing_quote;

	while (input[*i])
	{
		if (input[*i] == QUOTE || input[*i] == DOUBLE_QUOTE)
		{
			closing_quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != closing_quote)
				(*i)++;
			if (input[*i] == closing_quote)
				(*i)++;
		}
		if (input[*i] && input[*i] == SEMICOLON)
		{
			(*i)++;
			return ;
		}
		if (input[*i]
			&& (input[*i] != QUOTE && input[*i] != DOUBLE_QUOTE))
			(*i)++;
	}
}

t_list	*split_by_semicolons(t_shell *shell, char *input)
{
	t_list	*split_cmds;
	char	*cmd_line;
	int		start;
	int		end;

	end = 0;
	start = 0;
	split_cmds = NULL;
	cmd_line = NULL;
	while (input[start])
	{
		find_command_line(input, &end);
		cmd_line = fill_command_line(shell, input, start, end);
		ft_lstadd_back(&split_cmds, ft_lstnew(cmd_line));
		start = end;
		if (input[end])
			end++;
	}
	// print_list(split_cmds);
	return (split_cmds);
}

int	exit_failed(t_cmd *cmd)
{
	if (cmd && ft_strncmp(cmd->argv[0], "exit", 5) == 0 && exit_status == 1)
		return (1);
	return (0);
}

int	syntax_error(t_shell *shell)
{
	if (shell->cmds_list == NULL)
		return (1);
	return (0);
}

static void process_input(t_shell *shell, int flag)
{		
	t_list	*split_cmds;
	t_list	*split_cmds_head;
	
	split_cmds = split_by_semicolons(shell, shell->input);
	split_cmds_head = split_cmds;
	if (flag == PROMPT)
		free_set_null((void **)&shell->input);
	while (split_cmds)
	{
		tokenize(shell, split_cmds->content);
		free_set_null((void **)&split_cmds->content);
		if (shell->cmd_array == NULL)
			return ;
		parse(shell);
		if (&shell->cmd_array[0])
			exit_status = evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
		if (exit_failed(shell->cmds_list) || syntax_error(shell))
			break ;
		clear_nonessential_memory(shell);
		split_cmds = split_cmds->next;
	}
	ft_lstclear(&split_cmds_head, del);
}

// void	execute_minishell_script(t_shell *shell, char **argv, char **envp)
// {
// 	int		fd;
// 	int		ret;

// 	fd = open(argv[1], O_RDONLY);
// 	ret = 1;
// 	while (ret > 0)
// 	{
// 		ret = get_next_line(fd, &shell->input);
// 		if (ret <= 0)
// 			ft_exit(shell, NULL);
// 		store_environment(shell, envp);
// 		tokenize(shell, shell->input);
// 		if (shell->cmd_array == NULL) //in case of missing closing bracket / empty input
// 			return ;
// 		parse(shell);
// 		if (&shell->cmd_array[0])
// 			exit_status = evaluator(shell, shell->cmds_list, shell->nb_of_cmds);
// 		clear_nonessential_memory(shell);
// 	}
// 	clear_memory(shell);
// }

void	execute_minishell_from_string(t_shell *shell, char *arg, char **envp)
{
	shell->input = arg;
	store_environment(shell, envp);
	process_input(shell, STRING);
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
	// else if (argc == 2 && ft_strncmp(argv[1], "./", 2) == 0)
	// 	execute_minishell_script(&shell, argv, envp);
	else if (argc >= 3 && ft_strncmp(argv[1], "-c", 3) == 0)
		execute_minishell_from_string(&shell, argv[2], envp);
	else
	{
		ft_printf(2, "minishell: Wrong use. Try again !\n");
		exit_status = 42;
	}
	clear_memory(&shell);
	return (exit_status);
}
