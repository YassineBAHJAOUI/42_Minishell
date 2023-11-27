# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 16:49:35 by ybahjaou          #+#    #+#              #
#    Updated: 2023/11/13 16:49:36 by ybahjaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isdigit.c \
ft_itoa.c  ft_strncmp.c ft_memcmp.c ft_strlen.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
ft_strtrim.c ft_substr.c ft_strstr.c get_next_line.c fd_printf.c ft_putnbr_fd.c \
ft_lstadd_front.c ft_lstnew.c ft_lstlast.c ft_lstsize.c ft_lstadd_back.c ft_lstchr.c \
ft_lstclear.c ft_split_ws.c

OBJS = $(SRCS:.c=.o)

all:$(NAME)

%.o:%.c libft.h
	$(CC) $(CFLAGS) -c $<

$(NAME):$(OBJS)
	ar cr $(NAME) $(OBJS)


clean:
	rm -f $(OBJS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
