# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 16:11:01 by abonnel           #+#    #+#              #
#    Updated: 2021/07/16 10:51:57 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c\
				parsing/tokenizer.c\
				parsing/store_environment.c\
				parsing/parser.c\
				parsing/parser_redirections.c\
				parsing/parser_utils.c\
				parsing/parser_flags.c\
				parsing/parser_variables.c\
				utils/prompt.c\
				utils/calloc_shell.c\
				utils/clear_memory.c\
				utils/del.c\
				utils/error.c\
				utils/char_detection.c\
				utils/token_list_functions.c\
				utils/split_words_into_token.c\
				utils/sig_handler.c\
				utils/get_env.c\
				utils/put_env.c\
				utils/print_list.c\
				utils/sort_list.c\
				builtins/exit.c\
				builtins/cd.c\
				builtins/unset.c\
				builtins/export.c\
				builtins/pwd.c\
				builtins/echo.c\
				builtins/env.c
				

SRCSPATH= srcs/

OBJS_FILES = $(SRCS_FILES:.c=.o)

OBJSPATH= .objs/

SRCS = $(addprefix $(SRCSPATH),$(SRCS_FILES))

OBJS = $(addprefix $(OBJSPATH),$(OBJS_FILES))

NAME	= minishell

CC		= gcc

RM		= rm -rf

READLINE = 	-I /Users/$(USER)/.brew/opt/readline/include

CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address

DIR		=	.objs/parsing\
			.objs/utils\
			.objs/execution\
			.objs/builtins

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/minishell.h libft/libft.h libft/libft.a
			@mkdir -p $(OBJ_PATH) $(DIR)
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/ -I libft/ -I /Users/$(USER)/.brew/opt/readline/include

#verify that libft include works no relink
all:		previous $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L /Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft -g

# -I includes/readline/8.1/include/readline/ \
			-Lincludes/readline/8.1/lib

previous:
			@$(MAKE) -C ./libft

clean:
			$(RM) $(OBJSPATH)
			$(MAKE) clean -C ./libft

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re
