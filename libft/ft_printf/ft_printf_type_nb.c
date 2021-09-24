/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_nb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:00:57 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:15:37 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precise_nb(t_printf *t_data, char *nb, int nb_len)
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

int	padding_nb(t_printf t_data, char *nb, int nb_len)
{
	int			padding;

	padding = -1;
	if (nb[0] == '-' && t_data.spec != 'c')
		t_data.prec++;
	if (t_data.spec == 'p')
		t_data.width -= 2;
	if (nb_len > t_data.prec)
		padding = t_data.width - nb_len;
	else
		padding = t_data.width - t_data.prec;
	if (padding > 0)
		return (padding);
	else
		return (-1);
}

void	flag_print(t_printf *t_data, char *nb, int nb_len, int padding)
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

char	*get_arg_diuxp(t_printf *t_data, char *nb)
{
	if (t_data->spec == 'u')
		nb = ft_itoa(va_arg(t_data->parg, unsigned int));
	else if (t_data->spec == 'p')
	{
		nb = ft_itoabase(va_arg(t_data->parg, unsigned long long),
				"0123456789abcdef");
	}
	else if (t_data->spec == 'x')
	{
		nb = ft_itoabase(va_arg(t_data->parg, unsigned int),
				"0123456789abcdef");
	}
	else if (t_data->spec == 'X')
	{
		nb = ft_itoabase(va_arg(t_data->parg, unsigned int),
				"0123456789ABCDEF");
	}
	else
		nb = ft_itoa(va_arg(t_data->parg, int));
	return (nb);
}

void	print_nb(t_printf *t_data)
{
	int			padding;
	char		*nb;
	int			nb_len;

	nb = NULL;
	nb = get_arg_diuxp(t_data, nb);
	if (!nb)
		return ;
	if (nb[0] == '0' && t_data->prec == 0)
	{
		if (t_data->spec == 'p' && t_data->flag == '-')
			put_0x(t_data);
		print_padding(print_nb_norm(t_data), t_data);
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
