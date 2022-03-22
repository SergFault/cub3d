/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstepani <rstepani@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:33:00 by rstepani          #+#    #+#             */
/*   Updated: 2022/03/15 19:21:42 by rstepani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"

# define W_RES 1200
# define H_RES 600
# define TEX_W 1024
# define TEX_H 1024
# define BUFFER_SIZE 40
# define VALID_CHARS "01NSEW "

# define WALL_CH '1'
# define SPACE_CH ' '
# define X 0
# define Y 1

# define MEM_ERR "Error\nMemory allocation error.\n"
# define MAP_EXT_ERR "Error\nWrong file extension.\n"
# define BAD_FD "Error\nBad file descriptor error.\n"
# define MAP_VALID_ERR "Error\nMap validation error.\n"
# define META_VALID_ERR "Error\nMeta file validation error.\n"
# define BAD_FILE "Error\nFile read error.\n"
# define ARGS_ERROR "Error\nNumber of arguments is incorrect.\n"
# define TEXTURES_INIT_ERROR "Error\nInvalid textures file or doesn`t exits.\n"

# define ESC 53
# define LEFT 0
# define UP 13
# define RIGHT 2
# define DOWN 1
# define NORTH_SIDE 0
# define SOUTH_SIDE 1
# define WEST_SIDE 2
# define EAST_SIDE 3
# define CEIL 0
# define FLOOR 1
# define MV_SPEED 0.03
# define RT_SPEED 0.07

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_objs_number
{
	int	player;
}				t_objs_number;

typedef struct s_img{
	void	*img;
	char	*address;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_fire
{
	t_img	img[20];
	int		i;
}				t_fire;

typedef struct s_rend
{
	void	*mlx;
	void	*win;
	t_img	main_img;
	t_img	back_img;
	t_img	minimap;
	t_fire	fire;
	t_img	east;
	t_img	west;
	t_img	north;
	t_img	south;
	int		i;
}				t_rend;

typedef struct s_eng
{
	int		i;
	int		pos_int[2];
	int		step[2];
	int		texture[2];
	int		chosen_text;
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	dist_d[2];
	double	side_dist[2];
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex[2];
	double	tex_step;
	double	tex_pos;
	t_img	*image;
}				t_eng;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	cam_plane_x;
	double	cam_plane_y;
	int		move_front;
	int		move_back;
	int		move_right;
	int		move_left;
	int		turn_left;
	int		turn_right;
}				t_coordinates;

typedef struct s_game{
	t_coordinates	hero_pos;
	int				map_w;
	int				map_h;
	t_img			hero;
	char			**map;

}				t_game;

typedef struct s_dataset{
	t_rend			*rend;
	t_game			*game;
	char			*path_east;
	char			*path_west;
	char			*path_north;
	char			*path_south;
	int				fl_rgb[3];
	int				ce_rgb[3];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	double			k[256];
}				t_dataset;

/* utils */
double			ft_abs(double val);
void			init_data(t_dataset *set);
void			set_img_null(t_img *img);
size_t			ft_strlen(const char *s);
int				ft_sj_ff_dt(const char *s1, const char *s2, char **dest);
int				ft_strdup_free(const char *s1, char **dest);
int				map_init(t_dataset *set, char *argv);
void			ft_lst_del_str(void *str);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
t_list			*ft_lstnew(void *content);
char			*ft_strchr(const char *s, int c);
int				check_extension(char *argv);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strdup(const char *s);
void			*ft_error_null(char *message);
void			free_str_array(char **str_arr, int index);
int				validate_map(char **map, t_game *game);
int				get_next_line(int fd, char **line);
void			free_data(t_dataset *set);
int				free_map(char **map);
int				leave_game(t_dataset *set);
int				get_pixel(t_img *t_img, int s_x, int s_y);
void			put_pixel(t_img *data, int x, int y, unsigned int color);
int				ft_str_cons_only(char *str, char ch);
int				check_map_content(char **map);
int				process_key_pressed(int key, t_dataset *set);
void			movement_processor(t_dataset *set);
int				process_key_released(int key, t_dataset *set);
t_list			*lines_list(t_list *lines, char *path);
int				validate_lines(t_list *str_lines, t_dataset *set);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				check_n_skip_textures(t_list **list, t_dataset *set);
int				ft_is_digit(char ch);
int				check_n_skip_colors(t_list **list, t_dataset *set);
int				ft_str_cons_only_chars(char *str, char *str_ch);
int				ft_is_space(char ch);
int				check_n_skip_map(t_list **line_lst, t_dataset *set);
int				ft_atoi(const char *str);
char			**str_lines_to_arr(t_list *lines, t_game *game);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_dup_spaces(size_t size);
void			free_textures_paths(t_dataset *set);
t_coordinates	get_pos(t_game *game);
unsigned int	convert_rgb(const int rgb[3]);
void			fill_bg_img(t_dataset *set);
int				skip_spaces(char **str);
int				have_all_meta_data(t_dataset *set);
int				check_x_coordinate(t_dataset *set, double coordinate);
int				check_y_coordinate(t_dataset *set, double coordinate);
void			move_forward(t_dataset *set);
void			move_back(t_dataset *set);
void			move_left(t_dataset *set);
void			move_right(t_dataset *set);
unsigned int	shadows(unsigned int color, double y);
int				rend_init(t_dataset *set);
int				is_valid_color_pattern(char *str);
void			space_check_skip(char **str);

/*render*/
void			render_image(t_dataset *set);
void			calculate_ray(t_eng *e, int num);
void			calculate_texture_side(t_eng *e);
void			calculate_ray_step(t_eng *e);
void			calculate_crossover(t_eng *e, t_dataset *set);
void			calculate_normale_ray(t_eng *e);

#endif
