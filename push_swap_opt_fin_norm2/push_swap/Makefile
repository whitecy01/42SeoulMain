# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/19 12:05:04 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
SRCS = ./main/push_swap.c\
		./free/free_char.c\
		./split/input_split.c\
		./split/libft_changeint.c\
		./split/empty_overlap.c\
		./split/atoi_intchange.c\
		./doubleLinkedList/create_stacknode.c\
		./command/sa_sb_ss.c\
		./command/pa_pb.c\
		./command/ra_rb_rr.c\
		./command/rra_rrb_rrr.c\
		./sort/quick_sort.c\
		./sort/stackcount_pivot.c\
		./sort/three_underonly.c\
		./sort/sorting_algorithm.c\
		./sort/a_to_b.c\
		./sort/a_to_b2.c\
		./sort/b_to_a.c\
		./sort/b_to_a2.c\
		./sort/check_sorted_sor.c\
		./sort/three_underonlyhardcode.c\

OBJS = $(SRCS:.c=.o)
INCLUDE = head


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o : $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)



clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 
