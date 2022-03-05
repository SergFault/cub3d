STD_MAP		=	map.ber
SMALL_MAP	=	map1.ber
NAME 		=	cub3d
CC			=	clang
FLAGS		=	-g #-Wall -Wextra -Werror -std=c99  #-fsanitize=leak \
-fsanitize=address
LIB_BIN		=	mlx-linux/libmlx_Linux.a
MLX_DIR		=	mlx-linux
LIB			=	-L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz -lm
INCLUDES	=	includes/
HEADER		=	includes/cub3d.h
SRC			=	src/main.c \
				src/init.c \
				src/utils/abs.c \
				src/utils/map_utils.c \
				src/utils/ft_lst_del_str.c \
				src/utils/ft_lstadd_back.c \
				src/utils/ft_lstclear.c \
				src/utils/ft_lstdelone.c \
				src/utils/ft_lstnew.c \
				src/utils/get_next_line.c \
				src/utils/ft_strchr.c \
				src/utils/checker.c \
				src/utils/ft_putchar_fd.c \
				src/utils/ft_putnbr_fd.c \
				src/utils/ft_strdup.c \
				src/utils/ft_strlcpy.c \
				src/utils/ft_putstr_fd.c \
				src/utils/ft_error_null.c \
				src/utils/free_str_array.c \
				src/utils/get_next_line_utils.c \
				src/utils/leave_game.c \
				src/utils/mem_utils.c \
				src/utils/keyboard_processor.c \
				src/utils/render_utils.c \
				src/utils/draw_utils.c \
				src/utils/ft_str_cons_only.c \
				src/utils/checker_map_content.c

OBJS		= 	${SRC:.c=.o}

%.o:		%.c Makefile
			$(CC) $(FLAGS) -I$(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(LIB_BIN)
			$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(LIB_BIN):
			make -C $(MLX_DIR)

clean:
			make -C $(MLX_DIR) clean
			rm -f ${OBJS}
			rm -f ${OBJ_M}
			rm -f ${OBJ_B}
			rm -f valgrind-out.txt

fclean:		clean
			make -C $(MLX_DIR) clean
			rm -f ${LIB_BIN}
			rm -f ${NAME}

re:			fclean all

-include	deps.mk

deps.mk: 	$(SRC_B) $(SRC)
			$(CC) -MM -I$(INCLUDES) $^ > $@

val:		${NAME}
			valgrind \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./${NAME} ${SMALL_MAP}

val_bonus:	bonus
				valgrind \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--verbose \
				--log-file=valgrind-out.txt \
			./${NAME} ${SMALL_MAP}

.PHONY:		val re all clean fclean bonus val_bonus
