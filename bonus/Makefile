# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 21:32:35 by jaeyojun          #+#    #+#              #
#    Updated: 2023/06/19 22:29:57 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = checker
SRCS = check.c\
		bonus_atoi_intchange.c\
		bonus_create_stacknode.c\
		bonus_empty_overlap.c\
		bonus_free_char.c\
		bonus_input_split.c\
		bonus_libft_changeint.c\
		bonus_get_next_line_utils.c\
		bonus_get_next_line.c\


OBJS = $(SRCS:.c=.o)


INCLUDE = /head/checker.h


all : $(NAME) 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) 


.c.o : $(OBJS) 
		$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

		

bonus: all $(BONUS)

clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: clean fclean re 
