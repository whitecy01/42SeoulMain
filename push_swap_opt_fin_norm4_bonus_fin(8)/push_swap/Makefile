# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/22 17:48:32 by jaeyojun         ###   ########seoul.kr   #
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
INCLUDE = head/push_swap.h


BONUS = checker

# ./bonus/bonus_atoi_intchange.c\
# ./bonus/bonus_create_stacknode.c\
# ./bonus/bonus_empty_overlap.c\
# ./bonus/bonus_input_split.c\
# ./bonus/bonus_libft_changeint.c\
# ./bonus/bonus_free_char.c\

# ./bonus/bonus_atoi_intchange.o\
# ./bonus/bonus_create_stacknode.o\
# ./bonus/bonus_empty_overlap.o\
# ./bonus/bonus_input_split.o\
# ./bonus/bonus_libft_changeint.o\
# ./bonus/bonus_free_char.o\


SRCS_BONUS = check.c\
		bonus_atoi_intchange.c\
		bonus_create_stacknode.c\
		bonus_empty_overlap.c\
		bonus_free_char.c\
		bonus_input_split.c\
		bonus_libft_changeint.c\
		bonus_get_next_line_utils.c\
		bonus_get_next_line.c\
		bonus_pa_pb.c\
		bonus_ra_rb_rr.c\
		bonus_rra_rrb_rrr.c\
		bonus_sa_sb_ss.c\
		bonus_command.c\
		bonus_error.c\
		bonus_command_temp.c


# OBJS_BONUS = check.o\
# 		bonus_atoi_intchange.o\
# 		bonus_create_stacknode.o\
# 		bonus_empty_overlap.o\
# 		bonus_free_char.o\
# 		bonus_input_split.o\
# 		bonus_libft_changeint.o\
# 		bonus_get_next_line_utils.o\
# 		bonus_get_next_line.o\
# 		bonus_pa_pb.o\
# 		bonus_ra_rb_rr.o\
# 		bonus_rra_rrb_rrr.o\
# 		bonus_sa_sb_ss.o\
# 		bonus_command.o\
# 		bonus_error.o\
# 		bonus_command_temp.o

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INCLUDE_BONUS = checker.h
# 	gcc -Wall -Wextra -Werror -o $@ $(OBJS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 

#bonus
# helloWorld : helloworld.c
#     $(CC) -o $@ $<
$(BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) 
# $(BONUS) : $(OBJS_BONUS)
# 	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) 

# $(OBJS_BONUS) : $(SRCS_BONUS)
# 	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_BONUS)
#######

# .c.o : $(OBJS)
# 	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)
	
# .c.o : $(OBJS_BONUS)
# 	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<
		
# %.o : %.c
# 	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_BONUS)

bonus: all $(BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: clean fclean re 
