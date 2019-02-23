NAME = fractol
SRC = ./src/main.c ./src/mandelbrot.c ./src/keys.c ./src/sierp.c ./src/draw.c ./src/julia.c
SRC2 = ./libft/libft.a
OBJECTS = main.o keys.o mandelbrot.o
FLAGS = -g -Wall -Wextra -Werror
FLAGS2 = -Iincludes/ -I /usr/local/include -L /usr/local/lib -lmlx -lpthread -framework OpenGL -framework AppKit
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