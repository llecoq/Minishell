# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 11:39:25 by abonnel           #+#    #+#              #
#    Updated: 2021/07/01 15:04:18 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_printf.c ft_print_conversion.c ft_printf_type_nb.c \
		  ft_printf_type_char.c ft_printf_type_str.c ft_printf_type_hexa.c \

OBJS	= $(SRCS:.c=.o)

NAME	= libftprintf.a

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
# $(MAKE) -C ../
# cp ../libft.a $(NAME)
			ar -rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) clean -C ./libft

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
