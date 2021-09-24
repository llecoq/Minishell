/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:48:51 by abonnel           #+#    #+#             */
/*   Updated: 2021/09/24 15:16:01 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft.h"

typedef struct s_printf
{
	va_list		parg;
	char		*format;
	char		flag;
	int			width;
	int			prec;
	char		spec;
	int			nb_char;
	int			fd;
}				t_printf;

int				ft_printf(int fd, const char *str, ...);
void			print_conversion(t_printf *t_data, int *i);
int				specifier_is(t_printf *t_data, int i);
void			find_format(t_printf *t_data, int i, char *format);
void			ft_putchar(char c, t_printf *t_data);
void			print_nb(t_printf *t_data);
void			precise_nb(t_printf *t_data, char *nb, int nb_len);
void			print_hexa(t_printf *t_data);
void			print_padding(int padding, t_printf *t_data);
int				padding_nb(t_printf t_data, char *nb, int nb_len);
void			precise_nb(t_printf *t_data, char *nb, int nb_len);
void			print_char(t_printf *t_data);
void			flag_print(t_printf *t_data, char *nb, int nb_len, int padding);
void			printf_string(t_printf *t_data);
int				hexa_len(unsigned long long nb);
char			*ft_itoabase(unsigned long long nb, char *base);
void			print_perc(t_printf *t_data);
void			put_0x(t_printf *t_data);
int				print_nb_norm(t_printf *t_data);

#endif
