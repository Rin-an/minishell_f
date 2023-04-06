# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 21:22:37 by ssadiki           #+#    #+#              #
#    Updated: 2022/09/24 18:52:50 by ssadiki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = libft.h
FLAGS = -Werror -Wextra -Wall
CRT = ar -cr
RM = rm -rf

SRCS =$(wildcard *.c)

OBJS := $(SRCS:.c=.o)

all : $(NAME)

#Archive
$(NAME): $(OBJS)
	$(CRT) $@ $^

%.o : %.c $(INC)
	gcc $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
