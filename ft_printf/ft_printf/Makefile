# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:56:43 by jaeyojun          #+#    #+#              #
#    Updated: 2023/05/19 15:56:43 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c output_csp.c output_d.c output_xu.c
OBJS = $(SRCS:.c=.o)
INCLUDE = printf.h 

all: $(NAME)


$(NAME): $(OBJS)
	ar -rc $@ $(OBJS)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 