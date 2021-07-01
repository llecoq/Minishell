/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_nb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:00:57 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/22 13:47:41 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		precise_nb(t_printf *t_data, char *nb, int nb_len)
{
	int			i;

	i = 0;
	if (t_data->flag == '0')
		t_data->prec = t_data->width;
	if (nb[0] == '-')
	{
		ft_putchar('-', t_data);
		i++;
		(t_data->prec)++;
		if (t_data->flag == '0')
			(t_data->prec)--;
	}
	while (t_data->prec > nb_len)
	{
		ft_putchar('0', t_data);
		(t_data->prec)--;
	}
	while (i < nb_len)
	{
		ft_putchar(nb[i], t_data);
		i++;
	}
}

int			padding_nb(t_printf t_data, char *nb, int nb_len)
{
	int			padding;

	padding = -1;
	if (nb[0] == '-' && t_data.spec != 'c')
		t_data.prec++;
	if (t_data.spec == 'p')
		t_data.width -= 2;
	padding = t_data.width - ((nb_len > t_data.prec) ? nb_len : t_data.prec);
	return ((padding > 0) ? padding : -1);
}

void		flag_print(t_printf *t_data, char *nb, int nb_len, int padding)
{
	if (t_data->flag == '-')
	{
		if (t_data->spec == 'p')
			put_0x(t_data);
		precise_nb(t_data, nb, nb_len);
		print_padding(padding, t_data);
	}
	else
	{
		if (t_data->flag == 'z')
			print_padding(padding, t_data);
		if (t_data->spec == 'p')
			put_0x(t_data);
		precise_nb(t_data, nb, nb_len);
	}
}

char		*get_arg_diuxp(t_printf *t_data, char *nb)
{
	if (t_data->spec == 'u')
	{
		if (!(nb = ft_itoa(va_arg(t_data->parg, unsigned int))))
			return (0);
	}
	else if (t_data->spec == 'p')
	{
		if (!(nb = ft_itoabase(va_arg(t_data->parg, unsigned long long)
						, "0123456789abcdef")))
			return (0);
	}
	else if (t_data->spec == 'x' || t_data->spec == 'X')
	{
		if (!(nb = ft_itoabase(va_arg(t_data->parg, unsigned int),
						(t_data->spec == 'X') ? "0123456789ABCDEF" :
						"0123456789abcdef")))
			return (0);
	}
	else
	{
		if (!(nb = ft_itoa(va_arg(t_data->parg, int))))
			return (0);
	}
	return (nb);
}

void		print_nb(t_printf *t_data)
{
	int			padding;
	char		*nb;
	int			nb_len;

	nb = NULL;
	if (!(nb = get_arg_diuxp(t_data, nb)))
		return ;
	if (nb[0] == '0' && t_data->prec == 0)
	{
		if (t_data->spec == 'p' && t_data->flag == '-')
			put_0x(t_data);
		print_padding((t_data->spec == 'p') ? t_data->width - 2 : t_data->width,
				t_data);
		if (t_data->spec == 'p' && t_data->flag != '-')
			put_0x(t_data);
		free(nb);
		return ;
	}
	nb_len = ft_strlen(nb);
	padding = padding_nb(*t_data, nb, nb_len);
	flag_print(t_data, nb, nb_len, padding);
	free(nb);
}
