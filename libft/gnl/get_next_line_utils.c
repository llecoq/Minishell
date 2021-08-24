/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:59:31 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/23 17:05:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
	gnl_free_set_null(&s1);
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
		gnl_free_set_null(&s);
	return (new);
}
