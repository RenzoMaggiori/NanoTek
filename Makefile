##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
## File description:
## Makefile
##

SRC	=	$(wildcard src/*.cpp) \
		$(wildcard src/components/*.cpp) \
		$(wildcard src/circuits/*.cpp) \
		$(wildcard src/components/chipsets/*.cpp) \
		$(wildcard src/components/elementary/*.cpp) \
		$(wildcard src/components/special/*.cpp) \
	    $(wildcard src/components/chipsets/single/*.cpp) \

# Exclude main.cpp from the test compilation to avoid multiple main definitions
TEST_SRC = $(filter-out src/main.cpp, $(SRC)) $(wildcard tests/*.cpp)

CFLAGS	=	-I./include/ -g3

LDFLAGS = -lcriterion --coverage

NAME	=	nanotekspice

all: $(NAME)

$(NAME):
	g++ $(CFLAGS) -Wall -Werror -o $(NAME) $(SRC)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME) unit_tests *.gcno *.gcda

re:	fclean all

# New target for compiling and running tests
test_comp:
	g++ $(CFLAGS) $(TEST_SRC) $(LDFLAGS) -o unit_tests
	./unit_tests
