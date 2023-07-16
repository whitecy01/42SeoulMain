# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 13:58:29 by jaeyojun          #+#    #+#              #
#    Updated: 2023/07/16 15:06:09 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror


NAME = pipex
SRC = error_free.c\
		findpath_libft.c\
		path_split.c\
		pipex.c\
		split.c\
		combine_acces.c\
		
OBJ = $(SRC:.c=.o)

BONUS = bonus_pipex
BONUS_SRC = ./bonus/bonus_error_free.c\
		./bonus/bonus_findpath.c\
		./bonus/bonus_path_split.c\
		./bonus/bonus_pipex.c\
		./bonus/bonus_split.c\
		./bonus/bonus_get_next_line_utils.c\
		./bonus/bonus_get_next_line.c

BONUS_OBJ = $(BONUS_SRC:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 
	
$(BONUS) : $(BONUS_OBJ)
	$(CC) $(CFLAGS) -o $@ $(BONUS_OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<


bonus : all $(BONUS)

	
clean:
	rm -f $(OBJ)
	rm -f $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS)

re: fclean all

.PHONY: clean fclean re 