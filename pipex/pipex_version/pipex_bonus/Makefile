# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 13:58:29 by jaeyojun          #+#    #+#              #
#    Updated: 2023/07/13 17:40:27 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = bonus_error_free.c\
		bonus_findpath.c\
		bonus_path_split.c\
		bonus_pipex.c\
		bonus_split.c\
		bonus_get_next_line_utils.c\
		bonus_get_next_line.c


OBJ = $(SRC:.c=.o)
INCLUDE =  /head/pipex.h


all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 

.c.o : $(OBJS)
	$(CC) $(CFLAGS)  -c -o $@ $^ -I $(INCLUDE)


	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 