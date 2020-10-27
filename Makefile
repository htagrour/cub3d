# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htagrour <htagrour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 16:29:25 by htagrour          #+#    #+#              #
#    Updated: 2020/03/12 01:29:54 by htagrour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3d.a

SRC = drawing/detections_process.c\
	  drawing/draw_scene.c\
	  drawing/draw3d.c\
	  drawing/drawing_utils.c\
	  drawing/extra_utils.c\
	  drawing/math_utils.c\
	  drawing/update.c\
	  libft/ft_atoi.c\
	  libft/ft_bzero.c\
	  libft/ft_isdigit.c\
	  libft/ft_memcpy.c\
	  libft/ft_memset.c\
	  libft/ft_putchar_fd.c\
	  libft/ft_putstr_fd.c\
	  libft/ft_split.c\
	  libft/ft_strncmp.c\
	  libft/linked_list.c\
	  get_next_line/get_next_line.c\
	  get_next_line/get_next_line_utils.c\
	  read_file/extraction_funs.c\
	  read_file/fun_utils.c\
	  read_file/read_file.c\
	  read_file/utils.c\
	  screenshot/screen_shot.c\
	  main.c\
	  initialization.c

OBJECT = detections_process.o\
		 draw_scene.o\
		 draw3d.o\
		 drawing_utils.o\
		 extra_utils.o\
		 math_utils.o\
		 update.o\
		 ft_atoi.o\
		 ft_bzero.o\
		 ft_isdigit.o\
		 ft_memcpy.o\
		 ft_memset.o\
		 ft_putchar_fd.o\
		 ft_putstr_fd.o\
		 ft_split.o\
		 ft_strncmp.o\
		 linked_list.o\
		 get_next_line.o\
		 get_next_line_utils.o\
		 extraction_funs.o\
		 fun_utils.o\
		 read_file.o\
		 utils.o\
		 screen_shot.o\
		 main.o\
		 initialization.o

all: $(NAME)

$(NAME):

	gcc -Wall -Wextra -Werror -c $(SRC)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)
	gcc -Wall -Wextra -Werror libmlx.a cub3d.a -framework openGL -framework AppKit -o cub3D -D BUFFER_SIZE=10

clean:
	rm -f $(OBJECT) 
fclean: clean
	rm -f $(NAME)
	rm -f cub3D
re: fclean all
