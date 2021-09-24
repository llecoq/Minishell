/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:12:42 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 14:47:00 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	specifier_is(t_printf *t_data, int i)
{
	while (ft_isalpha((t_data->format)[i]) == 0 && (t_data->format)[i] != '%')
		i++;
	t_data->spec = (t_data->format)[i];
	return (++i);
}

void	find_flag(t_printf *t_data, int *i, char *format)
{
	if (format[*i] == '-')
	{
		t_data->flag = format[*i];
		if (format[*i + 1] == '0')
			*i += 1;
		*i += 1;
	}
	else if (format[*i] == '0')
	{
		if (format[*i + 1] == '-')
		{
			t_data->flag = '-';
			*i += 1;
		}
		else
			t_data->flag = '0';
		*i += 1;
	}
	while (format[*i] == '-' || format[*i] == '0')
		*i += 1;
}

void	find_width(t_printf *t_data, int *i, char *format)
{
	int	nb;

	if (format[*i] == '*')
	{
		nb = va_arg(t_data->parg, int);
		if (nb < 0)
			t_data->flag = '-';
		if (nb >= 0)
			t_data->width = nb;
		else
			t_data->width = nb * -1;
		*i += 1;
	}
	else if (ft_isdigit(format[*i]) == 1)
	{
		t_data->width = ft_atoi(format + *i);
		while (ft_isdigit(format[*i]) == 1)
			*i += 1;
	}
}

void	find_format(t_printf *t_data, int i, char *format)
{
	find_flag(t_data, &i, format);
	find_width(t_data, &i, format);
	if (format[i++] == '.' && t_data->spec != 'c')
	{
		t_data->prec = 0;
		if (format[i] == '*')
			t_data->prec = va_arg(t_data->parg, int);
		else if (ft_isdigit(format[i]) == 1)
			t_data->prec = ft_atoi(format + i);
		if (t_data->flag == '0' && t_data->prec >= 0 && t_data->spec != 's'
			&& t_data->spec != '%')
			t_data->flag = 'z';
	}
}

void	print_conversion(t_printf *t_data, int *i)
{
	int	after_spec;

	after_spec = specifier_is(t_data, *i);
	find_format(t_data, *i, t_data->format);
	*i = after_spec;
	if (t_data->spec == '%')
		print_perc(t_data);
	else if (t_data->spec == 'c')
		print_char(t_data);
	else if (t_data->spec == 's')
		printf_string(t_data);
	else if (t_data->spec == 'd' || t_data->spec == 'i'
		|| t_data->spec == 'u' || t_data->spec == 'p'
		|| t_data->spec == 'x' || t_data->spec == 'X')
		print_nb(t_data);
}
