CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp Span.cpp
OBJ = $(SRC:.cpp=.o)

INCLUDE = Span.hpp
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
