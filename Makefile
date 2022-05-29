# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 14:07:31 by anajmi            #+#    #+#              #
#    Updated: 2022/05/25 14:15:13 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = #-Wall -Werror -Wextra

SOURCE = \
		./main.c	\

OBJ = $(SOURCE:.c=.o)

LIBFT = ./Libft
ARLIB = $(LIBFT)/libft.a
ALLIBFT = make -C $(LIBFT)
CLEANLIBFT = make clean -C $(LIBFT)
FCLEANLIBFT = rm -f $(ARLIB)
RELIBFT = make re -C $(LIBFT)

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean re

%.o: %.c
	gcc $(CFLAGS) -c $^ -o $@

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(ALLIBFT)
	gcc $(OBJ) -lreadline $(ARLIB) -o $(NAME)
	@echo "$(C_GREEN)[PUSH SWAP MANDATORY CREATED!]$(C_RES)"

clean :
	$(CLEANLIBFT)
	rm -f $(OBJ)
	rm -f $(BOBJ)
	@echo "$(C_RED)[PUSH SWAP OBJECTS DELETED!]$(C_RES)"

fclean : clean
	$(FCLEANLIBFT)
	rm -f $(NAME)
	rm -f $(BNM)
	@echo "$(C_RED)[LIBFT ARCHIVE & PUSH SWAP EXECUTABLES DELETED!]$(C_RES)"

re : fclean all