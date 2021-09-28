# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 16:11:01 by abonnel           #+#    #+#              #
#    Updated: 2021/09/28 16:35:22 by llecoq           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	=	main.c\
				parsing/tokenizer.c\
				parsing/parser.c\
				parsing/utils/store_environment.c\
				parsing/utils/store_env_list.c\
				parsing/utils/parser_arg_list.c\
				parsing/utils/parser_find_command.c\
				parsing/utils/parser_utils.c\
				parsing/utils/parser_trim_quotes.c\
				parsing/utils/parser_flags.c\
				parsing/utils/parser_variables.c\
				parsing/utils/parser_heredoc.c\
				parsing/utils/parser_store_commands_list.c\
				parsing/utils/parser_split_semicolon.c\
				parsing/utils/split_words_into_token.c\
				parsing/utils/parser_variables_expansions.c\
				parsing/utils/tokenizer_utils.c\
				execution/evaluator.c\
				execution/process_input.c\
				execution/utils/create_pipe.c\
				execution/utils/exit_status.c\
				execution/utils/dup_redirections.c\
				execution/utils/create_redirection.c\
				execution/utils/execute_single_builtin.c\
				execution/utils/execute_child_process.c\
				execution/utils/search_expand_file_name.c\
				execution/utils/path_is_unset.c\
				execution/utils/ambiguous_redirect.c\
				execution/utils/build_file_path.c\
				prompt/prompt.c\
				prompt/sig_handler.c\
				utils/calloc_shell.c\
				utils/clear_memory.c\
				utils/del.c\
				utils/error.c\
				utils/char_detection.c\
				utils/token_list_functions.c\
				utils/token_list_functions2.c\
				utils/print_list.c\
				builtins/utils/get_env.c\
				builtins/utils/put_env.c\
				builtins/utils/sort_list.c\
				builtins/utils/format_plus_equal_str.c\
				builtins/utils/redir_single_builtin_cmd.c\
				builtins/utils/invalid_args_or_options.c\
				builtins/utils/append_value_to_var.c\
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

CFLAGS	= -Wall -Wextra -Werror  
# -g3 -fsanitize=address

DIR		=	.objs/parsing\
			.objs/parsing/utils\
			.objs/execution\
			.objs/execution/utils\
			.objs/builtins/utils\
			.objs/builtins\
			.objs/prompt\
			.objs/utils

$(OBJSPATH)%.o:		$(SRCSPATH)%.c includes/minishell.h libft/libft.h libft/libft.a
			@mkdir -p $(OBJ_PATH) $(DIR)
			$(CC) $(CFLAGS) -c $< -o $@ -I includes/ -I libft/\
			-I /Users/$(USER)/.brew/opt/readline/include

all:		previous $(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)\
			-L /Users/$(USER)/.brew/opt/readline/lib -lreadline -Llibft -lft -g

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
