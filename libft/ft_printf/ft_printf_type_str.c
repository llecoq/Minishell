/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 11:30:12 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 14:51:50 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precise_str(t_printf *t_data, char *s, int s_len)
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

static int	padding_norm_ternary(int prec, int s_len)
{
	if (prec > -1)
		return (prec);
	else
		return (s_len);
	return (0);
}

void	printf_string(t_printf *t_data)
{
	int			padding;
	int			s_len;
	char		*s;

	s = va_arg(t_data->parg, char *);
	if (!s)
		s = "(null)";
	s_len = ft_strlen(s);
	if (s_len < t_data->prec)
		t_data->prec = s_len;
	padding = t_data->width - padding_norm_ternary(t_data->prec, s_len);
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
