/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:48:39 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/12 16:08:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_struct(t_printf *t_data, int fd)
{
	t_data->flag = 'z';
	t_data->width = -1;
	t_data->prec = -1;
	t_data->spec = 'z';
	t_data->fd = fd;
}

void	ft_putchar(char c, t_printf *t_data)
{
	write(t_data->fd, &c, 1);
	(t_data->nb_char)++;
}

void	print_padding(int padding, t_printf *t_data)
{
	if (padding <= 0)
		return ;
	while (padding--)
	{
		if (t_data->flag == '0')
			ft_putchar('0', t_data);
		else
			ft_putchar(' ', t_data);
	}
}

void	print_perc(t_printf *t_data)
{
	if (t_data->flag == '-')
	{
		ft_putchar('%', t_data);
		print_padding(t_data->width - 1, t_data);
	}
	else
	{
		print_padding(t_data->width - 1, t_data);
		ft_putchar('%', t_data);
	}
}

int	ft_printf(int fd, const char *format, ...)
{
	int			i;
	t_printf	t_data;

	t_data.format = (char *)format;
	t_data.nb_char = 0;
	va_start(t_data.parg, format);
	i = 0;
	while (format[i])
	{
		init_struct(&t_data, fd);
		while (format[i] != '%' && format[i])
		{
			ft_putchar(format[i], &t_data);
			i++;
		}
		if (format[i] == '%' && format[i++])
			print_conversion(&t_data, &i);
	}
	va_end(t_data.parg);
	return (t_data.nb_char);
}
