# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/19 14:10:32 by jaeyojun         ###   ########seoul.kr   #
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

BONUS = checker
SRCS_BONUS = check.c
OBJS_BONUS = check.o

INCLUDE = head


# ifdef WITH_BONUS
# 	OBJ_CHECKER = $(OBJS_BONUS)
# 	OBJ = $(OBJS) 
# else
# 	OBJ = $(OBJS)
# endif

#OBJ = $(OBJS) $(OBJS_BONUS)
#OBJ = $(OBJS)
ifdef WITH_BONUS
   OBJ = $(OBJS) $(OBJS_BONUS)
else
   OBJ = $(OBJS)
endif


all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

#bonus##
$(BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS)

$(OBJS_BONUS) : $(SRCS_BONUS)
	$(CC) $(CFLAGS) -c -o $@ $< 
#######

.c.o : $(OBJS) 
		$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

bonus: all $(BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: clean fclean re 
