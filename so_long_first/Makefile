# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyojun <jaeyojun@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 17:32:30 by jaeyojun          #+#    #+#              #
#    Updated: 2023/07/25 20:36:11 by jaeyojun         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

SRC = get_next_line_utils.c\
		get_next_line.c\
		so_long_check_wall_count.c\
		so_long_DFS.c\
		so_long_error_free.c\
		so_long_key_press.c\
		so_long_map_read.c\
		so_long_show_map.c\
		so_long.c


OBJ = $(SRC:.c=.o)
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = so_long.h

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C mlx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I. -Lmlx -lmlx -framework OpenGl -framework AppKit

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	make clean -C mlx

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 