# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 09:59:43 by llecoq            #+#    #+#              #
#    Updated: 2021/08/16 09:59:44 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= libgnl.a

CC		= gcc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I.

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
