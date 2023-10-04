CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 

SRC = main.cpp Animal.cpp Cat.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp Brain.cpp
OBJ = $(SRC:.cpp=.o)

INCLUDE = Animal.hpp Cat.hpp Dog.hpp WrongAnimal.hpp WrongCat.hpp Polymorphism.hpp Brain.hpp
NAME = a.out

%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all : $(NAME)

$(NAME) : $(OBJ) $(INCLUDE)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
