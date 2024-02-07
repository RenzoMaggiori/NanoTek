##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-renzo.maggiori
## File description:
## Makefile
##

SRC	=	$(wildcard ./*.cpp)\
		${wildcard components/*.cpp} \
		${wildcard circuits/*.cpp} \
		${wildcard components/chipsets/*.cpp} \
		${wildcard components/elementary/*.cpp} \
		${wildcard components/special/*.cpp}

CFLAGS	=	-I./include/ -g3

NAME	=	nanotekspice

all:
		g++ -g3 -Wall -Werror -o $(NAME) $(SRC)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(NAME)

re:	fclean all