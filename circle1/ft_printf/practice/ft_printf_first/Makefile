CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c output_percent.c
OBJS = $(SRCS:.c=.o)
INCLUDE = printf.h 

all: $(NAME)


$(NAME): $(OBJS)
	ar -rc $@ $(OBJS)

.c.o: $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re 