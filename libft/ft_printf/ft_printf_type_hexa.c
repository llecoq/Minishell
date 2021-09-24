/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:30:11 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 14:41:06 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_0x(t_printf *t_data)
{
	ft_putchar('0', t_data);
	ft_putchar('x', t_data);
}

int	hexa_len(unsigned long long nb)
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
