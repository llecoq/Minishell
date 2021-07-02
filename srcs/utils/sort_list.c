/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:42:16 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/02 16:42:35 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_content(void **content, void **next_content)
{
	void	*tmp;

	tmp = *content;
	*content = *next_content;
	*next_content = tmp;
}

int	not_sorted(char *content, char *next_content)
{
	size_t	len;

	len = ft_strlen(content);
	if (len < ft_strlen(next_content))
		len = ft_strlen(next_content);
	if (ft_strncmp(content, next_content, len) > 0)
		return (1);
	return (0);
}

void	sort_alphabetically_list(t_list **export_list)
{
	t_list	*tmp_list;
	t_list	*list;

	list = *export_list;
	while (list)
	{
		tmp_list = list;
		while (tmp_list->next)
		{
			if (not_sorted(list->content, tmp_list->next->content))
				swap_content(&list->content, &tmp_list->next->content);
			tmp_list = tmp_list->next;
		}
		list = list->next;
	}
}
