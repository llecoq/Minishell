# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/29 10:45:55 by abonnel           #+#    #+#              #
#    Updated: 2021/09/24 15:11:22 by abonnel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_isalpha.c ft_toupper.c ft_tolower.c ft_isdigit.c ft_isalnum.c \
		  ft_isascii.c ft_isprint.c ft_strchr.c ft_strlen.c ft_strrchr.c \
		  ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c \
		  ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		  ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_substr.c \
		  ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		  hexa_len.c ft_itoabase.c ft_malloc.c\
		  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		  ft_lstmap.c ft_split_free.c ft_free_set_null.c\
		  ft_printf/ft_print_conversion.c ft_printf/ft_printf_type_char.c\
		  ft_printf/ft_printf_type_hexa.c ft_printf/ft_printf_type_nb.c\
		  ft_printf/ft_printf_type_str.c ft_printf/ft_printf.c

OBJS	= $(SRCS:.c=.o)

NAME	= libft.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)
			ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

