/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:02:28 by abonnel           #+#    #+#             */
/*   Updated: 2021/03/29 18:04:29 by abonnel          ###   ########lyon.fr   */
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
	res->next = NULL;
	return (res);
}
