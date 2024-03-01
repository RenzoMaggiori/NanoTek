##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
## File description:
## Makefile
##

SRC =	$(wildcard src/*.cpp) \
		$(wildcard src/components/*.cpp) \
		$(wildcard src/circuits/*.cpp) \
		$(wildcard src/components/chipsets/*.cpp) \
		$(wildcard src/components/elementary/*.cpp) \
		$(wildcard src/components/special/*.cpp) \
	    $(wildcard src/components/chipsets/single/*.cpp)

TEST_SRC = $(filter-out src/main.cpp, $(SRC)) $(wildcard tests/*.cpp)

CFLAGS = -I./src/ -I./src/components/elementary/ -I./src/components/special/ -I./src/components/chipsets/ -I./src/components/chipsets/single/ -I./src/circuits/ -g3

LDFLAGS = -lcriterion --coverage

NAME = nanotekspice
TEST_NAME = unit_tests

all: $(NAME)

$(NAME): $(SRC:.cpp=.o)
	g++ $(CFLAGS) $(SRC:.cpp=.o) -o $(NAME)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SRC:.cpp=.o)

fclean: clean
	rm -rf $(NAME) $(TEST_NAME) *.gcno *.gcda

re: fclean all

tests_run:
	g++ $(CFLAGS) $(TEST_SRC) $(LDFLAGS) -o unit_tests
	./unit_tests