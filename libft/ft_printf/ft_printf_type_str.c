/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:30:12 by abonnel           #+#    #+#             */
/*   Updated: 2020/12/21 12:00:52 by abonnel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		precise_str(t_printf *t_data, char *s, int s_len)
{
	int			i;

	if (t_data->prec == 0)
		return ;
	i = 0;
	if (t_data->prec > 0)
		while (t_data->prec-- > 0 && s[i])
			ft_putchar(s[i++], t_data);
	else
		while (i < s_len)
			ft_putchar(s[i++], t_data);
}

void		printf_string(t_printf *t_data)
{
	int			padding;
	int			s_len;
	char		*s;

	if (!(s = va_arg(t_data->parg, char *)))
		s = "(null)";
	s_len = ft_strlen(s);
	if (s_len < t_data->prec)
		t_data->prec = s_len;
	padding = t_data->width - ((t_data->prec > -1) ? (t_data->prec) : s_len);
	if (t_data->width > t_data->prec && t_data->prec > s_len)
		padding += t_data->prec - s_len;
	if (t_data->flag == '-')
	{
		precise_str(t_data, s, s_len);
		print_padding(padding, t_data);
	}
	else
	{
		print_padding(padding, t_data);
		precise_str(t_data, s, s_len);
	}
}
