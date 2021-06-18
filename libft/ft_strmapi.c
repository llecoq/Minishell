/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 09:28:11 by abonnel           #+#    #+#             */
/*   Updated: 2021/03/29 14:26:13 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			s_len;
	char		*result;
	int			i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!(result))
		return (NULL);
	i = -1;
	while (++i < s_len)
		result[i] = f(i, s[i]);
	result[i] = '\0';
	return (result);
}
