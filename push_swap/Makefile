# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/05/24 14:18:45 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRCS = 
OBJS = $(SRCS.c=.o)
INCLUDE = push_swap.h

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rc $@ $(OBJS)

.c.o : $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 
