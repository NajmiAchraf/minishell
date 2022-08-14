# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 14:07:31 by anajmi            #+#    #+#              #
#    Updated: 2022/06/27 15:52:16 by anajmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = #-Wall -Werror -Wextra

SOURCE = \
		./minishell.c	\
		./environment.c	\
		# ./sh.c	\

OBJ = $(SOURCE:.c=.o)

#*******************************#
#			LIBFT				#
#*******************************#

LIBFT = ./Libft
ARLIB = $(LIBFT)/libft.a
ALLIBFT = make -C $(LIBFT)
CLEANLIBFT = make clean -C $(LIBFT)
FCLEANLIBFT = rm -f $(ARLIB)
RELIBFT = make re -C $(LIBFT)

#*******************************#
#			LIBFT PLUS			#
#*******************************#

LIBPL = ./LibftPlus
ARPLS = $(LIBPL)/libftplus.a
ALLIBPL = make -C $(LIBPL)
CLEANLIBPL = make clean -C $(LIBPL)
FCLEANLIBPL = rm -f $(ARPLS)
RELIBPL = make re -C $(LIBPL)

#*******************************#
#			GNL					#
#*******************************#

GNL = ./get_next_line
ARGNL = $(GNL)/get_next_line.a
ALLGNL = make -C $(GNL)
CLEANGNL = make clean -C $(GNL)
FCLEANGNL = rm -f $(ARGNL)
REGNL = make re -C $(GNL)

#*******************************#
#			COLORS				#
#*******************************#

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

#*******************************#
#			EXECUTION			#
#*******************************#

.PHONY : all clean fclean re

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@

all : $(NAME)
	@echo "$(C_L_BLUE)[EXECUTE MINISHELL ...]$(C_RES)"
#	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell
#	@cat valgrind-out.txt 
	./minishell

$(NAME) : $(OBJ)
	$(ALLIBFT)
	$(ALLIBPL)
	$(ALLGNL)
	gcc $(OBJ) $(ARLIB) $(ARPLS) $(ARGNL) -lreadline -o $(NAME)
	@echo "$(C_GREEN)[MINISHELL MANDATORY CREATED!]$(C_RES)"

clean :
	$(CLEANLIBFT)
	$(CLEANLIBPL)
	$(CLEANGNL)
	rm -f $(OBJ)
	@echo "$(C_RED)[MINISHELL OBJECTS DELETED!]$(C_RES)"

fclean : clean
	$(FCLEANLIBFT)
	$(FCLEANLIBPL)
	$(FCLEANGNL)
	rm -f $(NAME)
	@echo "$(C_RED)[LIBFT ARCHIVE & MINISHELL EXECUTABLES DELETED!]$(C_RES)"

re : fclean all

