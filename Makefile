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

CFLAGS = -g #-Wall -Werror -Wextra

PARSE = \
	./Parsing/minishell.c \
	./Parsing/syntax_error.c \
	./Parsing/ft_environment.c \
	./Parsing/environment_utils.c \
	./Parsing/tokenizer.c \
	./Parsing/token_utils.c \
	./Parsing/token_utils2.c \
	./Parsing/expanding.c \
	./Parsing/parser.c \
	./Parsing/tools.c\
	# ./Parsing/pars_utils.c \
	# ./Parsing/pars_utils2.c \
	# ./Parsing/parsing/parse.c 

EXEC = \
	./Execution/execution.c	\
	./Execution/environment.c

SRCS = $(PARSE) $(EXEC)

LFLAGS = -lreadline -L/Users/ohrete/.brew/opt/readline/lib -I/Users/ohrete/.brew/opt/readline/include

OBJ = $(SRCS:.c=.o)

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
	gcc $(CFLAGS) -c $^ -o $@

all : $(NAME)
	@echo "$(C_L_BLUE)[EXECUTE MINISHELL ...]$(C_RES)"
	./minishell

$(NAME) : $(OBJ)
	$(ALLIBFT)
	$(ALLIBPL)
	$(ALLGNL)
	gcc $(OBJ) $(ARLIB) $(ARPLS) $(ARGNL) $(LFLAGS) -o $(NAME)
	@echo "$(C_GREEN)[MINISHELL MANDATORY CREATED!]$(C_RES)"

clean :
	@$(CLEANLIBFT)
	@$(CLEANLIBPL)
	@$(CLEANGNL)
	rm -f $(OBJ)
	@echo "$(C_RED)[MINISHELL OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(FCLEANLIBFT)
	@echo "$(C_RED)[LIBFT ARCHIVE DELETED!]$(C_RES)"
	@$(FCLEANLIBPL)
	@echo "$(C_RED)[LIBFT PLUS ARCHIVE DELETED!]$(C_RES)"
	@$(FCLEANGNL)
	@echo "$(C_RED)[GET NEXT LINE ARCHIVE DELETED!]$(C_RES)"
	@rm -f $(NAME)
	@echo "$(C_RED)[MINISHELL EXECUTABLES DELETED!]$(C_RES)"

re : fclean all

