# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohrete <ohrete@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 09:56:57 by ohrete            #+#    #+#              #
#    Updated: 2022/09/10 21:13:30 by ohrete           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c \
	syntax_error.c \
	ft_environment.c \
	environment_utils.c \
	tokenizer.c \
	token_utils.c \
	token_utils2.c \
	expanding.c \
	parser.c \
	tools.c\
	pipes_redirections.c\
	#pars_utils.c \
	#pars_utils2.c \
	#./parsing/parse.c 

OBJS = $(SRCS:%.c=%.o)
CONTROL = @stty -echoctl
LFLAGS = -lreadline -L/Users/ohrete/.brew/opt/readline/lib -I/Users/ohrete/.brew/opt/readline/include
CFLAGS = -fsanitize=address -g
LIBFT = ./libft/libft.a

all: $(NAME)
	
$(NAME): $(OBJS) $(LIBFT)
	$(CONTROL)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME) 

$(LIBFT) :
	cd ./libft && make

clean :
	rm -f $(OBJS)
	cd ./libft && make clean

fclean : clean
	rm -f $(NAME)
	cd ./libft && make fclean

re: fclean all