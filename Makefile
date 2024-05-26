CC=cc
CFLAGS=-Wall -Wextra -Werror
LFLAGS=-Llibft -lft -lreadline
SRC=main.c signal_handling.c command_handling.c utils.c
OBJ=$(SRC:%.c=%.o)
NAME=minishell

$(NAME): $(SRC) minishell.h
	$(CC) $(CFLAGS) -c $(SRC)
	cd libft && make
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

clean:
	rm -f $(OBJ)
	cd libft && make clean

fclean: clean
	rm -f $(NAME)
	cd libft && make fclean

all: $(NAME)

re: fclean all