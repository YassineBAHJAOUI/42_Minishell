# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 17:06:09 by ybahjaou          #+#    #+#              #
#    Updated: 2023/11/13 17:06:11 by ybahjaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = minishell

READLINE_PATH=$(shell brew --prefix readline)

CFLAGS = -Wall -Wextra -Werror -g -Iinclude

HEADER = ./include/builtins.h ./include/execution.h ./include/lexer.h ./include/minishell.h ./include/parser.h ./Libft-42/libft.h

LIBFT = Libft-42/libft.a

SRCS = main.c \
lexing/lexer_utils.c lexing/tokenizer.c lexing/lexer_lst.c\
parsing/ast_const.c parsing/parser.c parsing/utils_parser.c parsing/heredoc.c parsing/parser_priorities.c \
execution/execution.c execution/exec_pipe.c execution/exec_cmd.c execution/expand.c execution/exec_redir.c execution/expand_utils.c \
execution/exec_oper_subshell.c execution/wildcard.c execution/signal_exitstatus.c execution/utils_exec.c libgc/gc.c  libgc/gc_utils.c \
builtins/builtins.c builtins/pwd.c builtins/export.c builtins/echo.c builtins/cd.c builtins/utils.c builtins/unset.c builtins/env.c builtins/exit.c

OBJS=$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C Libft-42
#	$(CC) $(CFLAGS) -I $(READLINE_PATH)/include -o $(NAME) $^ -L Libft-42 -lft -L $(READLINE_PATH)/lib -lreadline 
	$(CC) $(CFLAGS) -o $(NAME) $^ -L Libft-42 -lft -lreadline 

%.o: %.c $(HEADER)
#	make -C Libft-42
#	$(CC) $(CFLAGS) -I $(READLINE_PATH)/include -c $< -o $@ -L Libft-42 -lft
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C Libft-42
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME) $(LIBFT)

re: fclean all 

.PHONY: clean fclean re all
