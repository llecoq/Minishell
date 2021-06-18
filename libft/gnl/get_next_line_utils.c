/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:58:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/03/29 17:47:26 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int				i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			nb_bytes;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	nb_bytes = count * size;
	while (nb_bytes)
	{
		ptr[nb_bytes - 1] = 0;
		nb_bytes--;
	}
	return (ptr);
}

char	*ft_strdup(const char *s1)
{
	int				s_len;
	char			*s_bis;
	int				i;

	s_len = ft_strlen(s1);
	s_bis = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!(s_bis))
		return (0);
	i = -1;
	while (s1[++i])
		s_bis[i] = s1[i];
	s_bis[i] = '\0';
	return (s_bis);
}

char	*strjoin_free1(char *s1, char *s2)
{
	int				s1_len;
	int				s2_len;
	char			*r;
	int				i;

	if (!s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	r = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!r)
		return (0);
	i = -1;
	while (++i < s1_len)
		r[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		r[s1_len + i] = s2[i];
	r[s1_len + i] = '\0';
	free_set_null(&s1);
	return (r);
}

char	*substr_gnl(char *s, unsigned int start, size_t len)
{
	char			*new;
	size_t			i;
	size_t			s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len > s_len)
		len = s_len;
	new = (char *)malloc(len + 1);
	if (!(new))
		return (0);
	i = -1;
	while (++i < len)
		new[i] = s[start + i];
	new[i] = '\0';
	if (start != 0)
		free_set_null(&s);
	return (new);
}
