.SUFFIX: .c.o

SRCS = ft_check.c ft_four_five.c ft_libft_str.c ft_libft.c ft_list_adddel.c ft_list.c ft_number.c \
	ft_over_five.c ft_push.c ft_rotate.c ft_swap.c ft_two_three.c push_swap.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

all : $(NAME)

$(NAME) : $(OBJS)
	
	gcc -Wall -Wextra -Werror -o $@ $(OBJS)

clean :

	rm -f $(OBJS);

fclean: clean

	rm -f $(NAME)

re: fclean all
