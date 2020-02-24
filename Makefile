# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltammie <ltammie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 19:18:13 by ltammie           #+#    #+#              #
#    Updated: 2020/02/09 00:28:08 by sauron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


GCC = gcc -Wall -Wextra -Werror
NAME = fdf
SRCS = main.c\
		start.c\
		dda.c\
		draw_image.c\
		read_map_data.c\
		controls.c\
		other.c\
		projections.c\
		rotations.c\
		convert_point.c
OBJS = $(SRCS:.c=.o)
HEAD = -c -I fdf.h
LIB = -L libft -lft -L minilibx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

%.o: %.c
		$(GCC) -c $<

lib:
		make -C libft
		make -C minilibx

$(NAME): $(OBJS) lib
		$(GCC) $(OBJS) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJS)
		make -C libft clean

fclean: clean
		rm -f $(NAME)
		make -C libft fclean
		make -C minilibx clean

re: fclean all
