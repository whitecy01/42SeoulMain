# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 13:58:29 by jaeyojun          #+#    #+#              #
#    Updated: 2023/07/07 16:35:55 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRC = error_free.c\
		findpath.c\
		path_split.c\
		pipex.c\
		split.c\

OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h


all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) 

.c.o : $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $^ -I $(INCLUDE)


	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 