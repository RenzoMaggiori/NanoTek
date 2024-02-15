##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
## File description:
## Makefile
##

SRC	=	$(wildcard src/*.cpp)\
		${wildcard src/components/*.cpp} \
		${wildcard src/circuits/*.cpp} \
		${wildcard src/components/chipsets/*.cpp} \
		${wildcard src/components/elementary/*.cpp} \
		${wildcard src/components/special/*.cpp}

CFLAGS	=	-I./include/ -g3

NAME	=	nanotekspice

all:
		g++ -g3 -Wall -Werror -o $(NAME) $(SRC)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re:	fclean all