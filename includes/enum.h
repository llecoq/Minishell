/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:09:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/09/06 15:27:22 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

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
};

enum	e_export
{
	EXPORT_LIST,
	ENV_LIST,
};

enum	e_builtins
{
	CD,
	ENV,
	PWD,
	UNSET,
	EXPORT,
};

#endif