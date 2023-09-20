CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Zombie.cpp randomChump.cpp newZombie.cpp
OBJ = $(SRC:.cpp=.o)

NAME = Zombie

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
