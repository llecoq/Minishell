/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:30:11 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/22 13:39:46 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			put_0x(t_printf *t_data)
{
	ft_putchar('0', t_data);
	ft_putchar('x', t_data);
}

int				hexa_len(unsigned long long nb)
{
	int						nb_len;

	nb_len = 1;
	while (nb >= 16)
	{
		nb_len++;
		nb /= 16;
	}
	return (nb_len);
}

char			*ft_itoabase(unsigned long long nb, char *base)
{
	int						nb_len;
	char					*nb_string;

	nb_len = 0;
	nb_len = hexa_len(nb);
	if (!(nb_string = (char *)ft_calloc(sizeof(char), (nb_len + 1))))
		return (0);
	nb_string[nb_len--] = '\0';
	while (nb >= 16)
	{
		nb_string[nb_len] = base[nb % 16];
		nb_len--;
		nb /= 16;
		if (nb_len < 0)
			break ;
	}
	nb_string[nb_len] = base[nb % 16];
	return (nb_string);
}
