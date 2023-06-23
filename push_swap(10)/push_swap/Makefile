# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 14:11:15 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/23 13:42:00 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
NAME = push_swap
SRCS = push_swap.c\
		free_char.c\
		input_split.c\
		libft_changeint.c\
		empty_overlap.c\
		atoi_intchange.c\
		create_stacknode.c\
		sa_sb_ss.c\
		pa_pb.c\
		ra_rb_rr.c\
		rra_rrb_rrr.c\
		quick_sort.c\
		stackcount_pivot.c\
		three_underonly.c\
		sorting_algorithm.c\
		a_to_b.c\
		a_to_b2.c\
		b_to_a.c\
		b_to_a2.c\
		check_sorted_sor.c\
		three_underonlyhardcode.c\

OBJS = $(SRCS:.c=.o)

BONUS = checker
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

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 

$(BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<


bonus: all $(BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: clean fclean re 
