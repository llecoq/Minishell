/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:02:28 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/07 15:25:30 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list			*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (!(res))
		return (NULL);
	res->content = content;
	res->variable = 1;
	res->next = NULL;
	return (res);
}
