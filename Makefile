NAME = minishell
SRCS = $(wildcard mandatory/*.c)\
	  $(wildcard  mandatory/parsing/*.c)\
	  $(wildcard mandatory/execution/*.c)\
	  $(wildcard mandatory/expansion/*.c)\

HEADER = mandatory/minishell.h
RM = rm -f
LIBFT = libft/libft.a
FLAGS = -Werror -Wall -Wextra
MAKE = make

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS) $(LIBFT)
	gcc $(OBJS) -lreadline -L/Users/ssadiki/.brew/opt/readline/lib -L libft -o $(NAME) $(LIBFT)

%.o : %.c $(HEADER)
	gcc $(FLAGS) -I/Users/ssadiki/.brew/opt/readline/include -o $@ -c $<

all : $(NAME)

$(LIBFT) :
	$(MAKE) -C libft

clean:
	$(RM) $(OBJS)
	cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean

re: fclean all

.PHONY: clean fclean all re
