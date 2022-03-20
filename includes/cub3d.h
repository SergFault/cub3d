#ifndef _CUB3D_H_
#define _CUB3D_H_

#include <stdio.h>/////

#define screen_width 1200
#define screen_height 600
#define texWidth 1024
#define texHeight 1024
#define mapWidth 24
#define mapHeight 24
#define BUFFER_SIZE 40
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
# define TEXTURES_META_ERROR "Error\nInvalid textures path format.\n"
# define TEXTURES_INIT_ERROR "Error\nInvalid textures file or doesn`t exits.\n"

#define WALL_PATH "./textures/0.png"//"./textures/redbrick1.xpm"

# define ESC 53//65307
# define LEFT 0//97
# define UP 13//119
# define RIGHT 2//100
# define DOWN 1//115
# define TRANSPARENCY 0xFFFFFFFF
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define NORTH_SIDE 0
# define SOUTH_SIDE 1
# define WEST_SIDE 2
# define EAST_SIDE 3
# define WALL_GAP 0.1
# define CEIL 0
# define FLOOR 1
# define YES 1
# define NO 0
# define MV_SPEED 0.12
# define RT_SPEED 0.07

#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"

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
	int		minimap_x;
	int 	minimap_y;
	t_fire	fire;
	t_img	east;
	t_img	west;
	t_img	north;
	t_img	south;
	int		i;
}				t_rend;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double dir_x;
	double dir_y;
	double cam_plane_x;
	double cam_plane_y;
	int move_front;
	int move_back;
	int move_right;
	int move_left;
	int turn_left;
	int turn_right;
}				t_coordinates;

typedef struct s_env
{
	t_coordinates	pos;
}				t_env;

typedef struct s_game{
	t_coordinates	hero_pos;
	int				map_width;
	int				map_height;
	t_img			hero;
	char			**map;

}				t_game;

typedef struct s_draw_data
{
	int		x;
	int		y;
	float	off_x;
	float	off_y;
	int		s_x;
	int		s_y;
	int		d_x;
	int		d_y;
	int		color;
}				t_draw_data;

typedef struct s_dataset{
	t_rend	*rend;
	t_game	*game;
	char	*path_east;
	char	*path_west;
	char	*path_north;
	char	*path_south;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	double	k[256];
}				t_dataset;

/* utils */
double ft_abs(double val);
void	init_data(t_dataset *set);
void	set_img_null(t_img *img);
void	game_init(t_game *game);
size_t	ft_strlen(const char *s);
int	ft_sj_ff_dt(const char *s1, const char *s2, char **dest);
int	ft_strdup_free(const char *s1, char **dest);
//static int	read_fd(char **line, char *buffer[], char **cache, int fd);
int	map_init(t_dataset *set, char *argv);
void	ft_lst_del_str(void *str);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list **lst, int c, void (*del)(void*));
t_list	*ft_lstnew(void *content);
char	*ft_strchr(const char *s, int c);
int	check_extension(char *argv);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);
void	*ft_error_null(char *message);
void	free_str_array(char **str_arr, int index);
int	validate_map(char **map, t_game *game);
int	get_next_line(int fd, char **line);
void	free_data(t_dataset *set);
int	free_map(char **map);
int	leave_game(t_dataset *set);
int	process_key(int key, t_dataset *set);
int	game_loop(t_dataset *set);
int	get_pixel(t_img *t_img, int s_x, int s_y);
void	put_pixel(t_img *data, int x, int y, unsigned int color);
int	ft_str_cons_only(char *str, char ch);
int	check_map_content(char **map);
int	process_key_pressed(int key, t_dataset *set);
void movement_processor(t_dataset *set);
int process_key_released(int key, t_dataset *set);
t_list	*lines_list(t_list *lines, char *path);
int validate_lines(t_list *str_lines, t_dataset *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_no_spaces(char *str);
void arr_to_zero(int *arr, int size);
int check_n_skip_textures(t_list **list, t_dataset *set);
int ft_is_digit(char ch);
int check_n_skip_colors(t_list **list, t_dataset *set);
int	ft_str_cons_only_chars(char *str, char *str_ch);
int	ft_is_space(char ch);
int check_n_skip_map(t_list **line_lst, t_dataset *set);
int	ft_atoi(const char *str);
//void	set_rgb_arr(const int *src, int *dst);
char	**str_lines_to_arr(t_list *lines, t_game *game);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_dup_spaces(size_t size);
void	free_textures_paths(t_dataset *set);
t_coordinates	get_pos(t_game *game);
unsigned int	convert_rgb(const int rgb[3]);
unsigned int	calc_shadows(unsigned int color, int y, double k[256]);
void	fill_bg_img(t_dataset *set);
int skip_spaces(char **str);
int have_all_meta_data(t_dataset *set);
int		process_mouse(int x, int y, t_dataset *set);
int		check_x_coordinate(t_dataset *set, double coordinate);
int		check_y_coordinate(t_dataset *set, double coordinate);
void	move_forward(t_dataset *set);
void	move_back(t_dataset *set);
void	move_left(t_dataset *set);
void	move_right(t_dataset *set);




#endif
