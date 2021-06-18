/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 08:42:34 by abonnel           #+#    #+#             */
/*   Updated: 2021/03/29 14:26:39 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			length;

	length = 0;
	while (s[length])
		length++;
	while (length >= 0)
	{
		if (s[length] == c)
			return ((char *)s + length);
		length--;
	}
	return (0);
}
