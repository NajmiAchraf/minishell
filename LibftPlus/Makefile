# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 20:14:52 by anajmi            #+#    #+#              #
#    Updated: 2022/09/25 22:28:38 by ohrete           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftplus.a

CFLAGS = -Wall -Werror -Wextra

SRC =	\
	./ft_free.c		\
	./ft_isupper.c	\
	./ft_islower.c	\
	./ft_strcmp.c	\
	./ft_lstlen.c	\
	./ft_lstslen.c	\
	./ft_swap_dp.c	\
	./ft_swap_tp.c	\
	./my_isalnum.c	\
	./my_strdup.c	\
	./my_strjoin.c

OBJS = $(SRC:.c=.o)

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean re

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@echo "$(C_GREEN)[LIBFT PLUS CREATED!]$(C_RES)"

clean :
	@rm -f $(OBJS) $(OBBS)
	@echo "$(C_RED)[LIBFT PLUS OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(C_RED)[LIBFT PLUS ARCHIVE DELETED!]$(C_RES)"

re : fclean all