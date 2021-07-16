/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:49:52 by abonnel           #+#    #+#             */
/*   Updated: 2021/07/16 17:15:18 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	find_builtin_function(char *cmd_name, t_token *cmd)
{
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		cmd->ft_builtin = &ft_cd;
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		cmd->ft_builtin = &ft_pwd;
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		cmd->ft_builtin = &ft_env;
	else if (ft_strncmp(cmd_name, "echo", 5) == 0)
		cmd->ft_builtin = &ft_echo;
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		cmd->ft_builtin = &ft_exit;
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		cmd->ft_builtin = &ft_unset;
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		cmd->ft_builtin = &ft_export;
	else
		cmd->ft_builtin = NULL;
}

static char	*look_for_cmd_path(char *cmd_name, t_list *env_path)
{
	int			fd;
	char		*path_with_cmd_name;
	
	fd = 0;
	while (env_path)
	{
		path_with_cmd_name = ft_strjoin(env_path->content, cmd_name);
		fd = open(path_with_cmd_name, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			return (path_with_cmd_name);
		}
		free(path_with_cmd_name);
		env_path = env_path->next;
	}
	return (NULL);
}

static int	cmd_search(t_token *cmd, t_shell *shell)
{
	if (cmd->word[0] == '\0' || !is_word(cmd->word))
	{
		error(shell, CMD_NOT_FOUND, cmd->word);
		return (CMD_NOT_FOUND);
	}
	find_builtin_function(cmd->word, cmd);
	if (cmd->ft_builtin == NULL)
	{
		cmd->cmd_path = look_for_cmd_path(cmd->word, shell->path);
		if (cmd->cmd_path == NULL)
		{
			error(shell, CMD_NOT_FOUND, cmd->word);
			return (CMD_NOT_FOUND);
		}
	}
	return (0);
}

void	find_command(t_token **cmd_array, t_shell *shell)
{
	int			i;
	t_token		*token;
	
	i = 0;
	while (cmd_array[i])
	{
		if (cmd_array[i]->error == 0)
			token = cmd_array[i];
		else
			token = NULL;
		while (token)
		{	
			if (token->cmd == 1)
			{
				if (cmd_search(token, shell) == CMD_NOT_FOUND)
					cmd_array[i]->error = 1;
				break;
			}
			token = token->next;
		}
		i++;
	}
}
