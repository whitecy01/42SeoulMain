# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/05 18:15:42 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRCS = ./main/push_swap.c \
		./split/input_split.c\
		./split/libft_changeint.c\
		./doubleLinkedList/create_stacknode.c\
		./command_sort/sa_sb_ss.c\
		./command_sort/sorting_algorithm.c\
		./command_sort/pa_pb.c

OBJS = $(SRCS:.c=.o)
INCLUDE = head


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.c.o : $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)
	


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 
