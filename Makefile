CC=cc
CFLAGS=-Wall -Wextra -Werror
#CFLAGS=
IFLAGS=-I includes -I libft
LFLAGS=-Llibft -lft -lreadline
OBJDIR=objects/
SRCDIR=sources/
SRC=$(wildcard $(SRCDIR)*.c)
OBJ=$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SRC:.c=.o))
ICL=$(wildcard includes/*.h)
NAME=minishell

$(NAME): $(OBJ) $(ICL)
	cd libft && make
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(ICL)
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	cd libft && make clean

fclean: clean
	rm -f $(NAME)
	cd libft && make fclean

all: $(NAME)

re: fclean all