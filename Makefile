STD_MAP		=	map.cub
SMALL_MAP	=	map1.ber
NAME 		=	cub3d
CC			=	clang
FLAGS		=	-g -Wall -Wextra -Werror #-std=c99  #-fsanitize=leak \
FLAGS 		+= -MMD -MP
-fsanitize=address
LIB_BIN		=	libmlx.dylib
MLX_DIR		=	minilibx_mms_20200219
LIB			=	-L. -lmlx -framework OpenGL -framework AppKit
INCLUDES	=	includes/
HEADER		=	includes/cub3d.h
SRC			=	src/main.c \
				src/initialize/init.c \
				src/utils/abs.c \
				src/validation/map_utils.c \
				src/validation/validate_lines.c \
				src/utils/ft_lst_del_str.c \
				src/utils/ft_lstadd_back.c \
				src/utils/ft_lstclear.c \
				src/utils/ft_dup_spaces.c \
				src/utils/arr_to_zero.c \
				src/utils/ft_lstdelone.c \
				src/utils/ft_lstnew.c \
				src/utils/position.c \
				src/utils/ft_strjoin.c \
				src/utils/ft_is_digit.c \
				src/utils/ft_strncmp.c \
				src/utils/get_next_line.c \
				src/utils/ft_strchr.c \
				src/validation/checker.c \
				src/utils/ft_putchar_fd.c \
				src/utils/ft_putnbr_fd.c \
				src/utils/ft_strdup.c \
				src/validation/check_n_skip_textures.c \
				src/utils/ft_strlcpy.c \
				src/utils/ft_putstr_fd.c \
				src/utils/ft_error_null.c \
				src/utils/set_rgb_arr.c \
				src/utils/ft_itoa.c \
				src/utils/free_str_array.c \
				src/utils/get_next_line_utils.c \
				src/utils/leave_game.c \
				src/utils/ft_atoi.c \
				src/utils/mem_utils.c \
				src/utils/ft_is_space.c \
				src/game_controller/keyboard_processor.c \
				src/game_controller/movement_processor.c \
				src/game_controller/check_coordinate.c \
				src/game_controller/move_processor.c \
				src/render/render_utils.c \
				src/render/render_calculations.c \
				src/render/draw_utils.c \
				src/render/fill_background.c \
				src/utils/ft_str_cons_only.c \
				src/validation/checker_map_content.c \
				src/validation/check_n_skip_colors.c \
				src/validation/check_n_skip_colors_2.c \
				src/validation/skip_count_spaces.c \
                src/validation/have_all_meta_data.c \
				src/validation/check_n_skip_map.c \
				src/utils/ft_no_spaces.c

OBJS		= 	${SRC:.c=.o}

%.o:		%.c Makefile $(HEADER)
			$(CC) $(FLAGS) -I$(INCLUDES) -I$(MLX_DIR) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(LIB_BIN)
			$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(LIB_BIN):
			make -C $(MLX_DIR)
			cp $(MLX_DIR)/$(LIB_BIN) $(LIB_BIN)

clean:
			make -C $(MLX_DIR) clean
			rm -f $(OBJS)
			rm -f $(OBJ_M)
			rm -f $(OBJ_B)
			rm -f valgrind-out.txt

fclean:		clean
			make -C $(MLX_DIR) clean
			rm -f $(LIB_BIN)
			rm -f $(NAME)

re:			fclean all


deps.mk: 	$(SRC_B) $(SRC)
			$(CC) -MM -I$(INCLUDES) $^ > $@

val:		${NAME}
			valgrind \
			--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./${NAME} ${STD_MAP}

-include $(SRCS:.c=.d)

.PHONY:		val re all clean fclean bonus val_bonus
