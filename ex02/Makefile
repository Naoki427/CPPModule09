NAME = PmergeMe
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra
CXXFLAGS += -std=c++98
CXXFLAGS += -fsanitize=address -g

SRC =	main.cpp \
		PmergeMe.cpp \

OBJ = $(SRC:.cpp=.o)

RM = rm -rf

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

bonus: all

re: fclean all