/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:09:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/26 15:41:54 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum	e_process
{
	CHILD_PROCESS,
	PARENT_PROCESS,
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