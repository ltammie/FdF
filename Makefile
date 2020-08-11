GCC = gcc -Wall -Wextra -Werror

NAME = fdf

INC_DIR = includes/
SRC_DIR = src/

SRCS = $(SRC_DIR)main.c\
		$(SRC_DIR)start.c\
		$(SRC_DIR)dda.c\
		$(SRC_DIR)draw_image.c\
		$(SRC_DIR)read_map_data.c\
		$(SRC_DIR)controls.c\
		$(SRC_DIR)other.c\
		$(SRC_DIR)projections.c\
		$(SRC_DIR)rotations.c\
		$(SRC_DIR)convert_point.c\
		$(SRC_DIR)error.c

OBJS = $(SRCS:.c=.o)
LIB = -L libft -lft -L minilibx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

%.o: %.c
		$(GCC) -c $< -o $@ -I $(INC_DIR)

lib:
		make -C libft
		make -C minilibx

$(NAME): $(OBJS) $(INC_DIR)fdf.h $(INC_DIR)keys.h lib
		$(GCC) $(OBJS) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C minilibx clean

re: fclean all
