NAME = fractol
SRC = ./src/main.c ./src/mandelbrot.c ./src/utils.c \
	./src/keys.c ./src/julia.c ./src/duck.c ./src/random.c
SRC2 = ./libft/libft.a
OBJECTS = main.o keys.o mandelbrot.o julia.o duck.o random.o utils.o
FLAGS = -g -Wall -Wextra -Werror
FLAGS2 = -I ./includes/ -I /usr/local/include -L /usr/local/lib -lmlx -lpthread -framework OpenGL -framework AppKit
FLAGS_LINUX = -I ./includes_linux/ /usr/X11/lib/libmlx.a  -lXext -lX11 -lm -lpthread

all: $(NAME)

linux:
	make re -C libft/
	sudo gcc $(FLAGS) $(SRC) $(SRC2) $(FLAGS_LINUX) -o $(NAME)

$(NAME):
	make re -C libft/
	gcc $(FLAGS) $(SRC) -Iincludes/ -c
	gcc $(FLAGS) $(FLAGS2) $(OBJECTS) $(SRC2) -o $(NAME)

clean:
	make clean -C libft/
	/bin/rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)

re: fclean all

re_linux: fclean linux
