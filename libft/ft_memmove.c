/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:23:06 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/07 17:13:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	char			*dst_bis;
	const char		*src_bis;

	src_bis = src;
	dst_bis = dst;
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			dst_bis[i] = src_bis[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (len--)
			dst_bis[len] = src_bis[len];
	}
	return (dst);
}
