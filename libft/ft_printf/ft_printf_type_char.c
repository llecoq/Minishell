/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:06:25 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:15:48 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_printf *t_data)
{
	char		c;
	int			padding;

	c = (char)va_arg(t_data->parg, int);
	padding = padding_nb(*t_data, &c, 1);
	if (t_data->flag == '-')
	{
		ft_putchar(c, t_data);
		print_padding(padding, t_data);
	}
	else
	{
		if (t_data->flag == 'z')
			print_padding(padding, t_data);
		if (t_data->flag == '0')
			while (padding-- && padding >= 0)
				ft_putchar('0', t_data);
		ft_putchar(c, t_data);
	}
}

int	print_nb_norm(t_printf *t_data)
{
	if (t_data->spec == 'p')
		return (t_data->width - 2);
	else
		return (t_data->width);
}
