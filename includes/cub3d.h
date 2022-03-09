#ifndef _CUB3D_H_
#define _CUB3D_H_

#define screen_width 640
#define screen_height 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define BUFFER_SIZE 40
# define VALID_CHARS "01NSEW"


# define WALL_CH '1'


# define MEM_ERR "Error\nMemory allocation error.\n"
# define MAP_EXT_ERR "Error\nWrong file extension.\n"
# define BAD_FD "Error\nBad file descriptor error.\n"
# define MAP_VALID_ERR "Error\nMap validation error.\n"
# define BAD_FILE "Error\nFile read error.\n"
# define ARGS_ERROR "Error\nNumber of arguments is incorrect.\n"


#define WALL_PATH "./textures/redbrick.xpm"


# define ESC 65307
# define LEFT 97
# define UP 119
# define RIGHT 100
# define DOWN 115
# define TRANSPARENCY 0xFF000000
# define BLACK 0x00000000
# define WHITE 0xFFFFFFFF
# define RED 0x00FF0000
# define MV_SPEED 0.01
# define RT_SPEED 0.01
# define NORTH_SIDE 1
# define SOUTH_SIDE 2
# define WEST_SIDE 3
# define EAST_SIDE 4
# define WALL_GAP 0.1



#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>




typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

typedef struct s_objs_number
{
	int	collectable;
	int	exit;
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

typedef struct s_rend
{
	void	*mlx;
	void	*win;
	t_img	main_img;
	t_img	east;
	t_img	west;
	t_img	north;
	t_img	south;
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
	int				win;
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
}				t_dataset;

/* utils */
double ft_abs(double val);
void	init_data(t_dataset *set);
void	set_img_null(t_img *img);
void	game_init(t_game *game);
size_t	ft_strlen(const char *s);
int	ft_sj_ff_dt(const char *s1, const char *s2, char **dest);
int	ft_strdup_free(const char *s1, char **dest);
static int	read_fd(char **line, char *buffer[], char **cache, int fd);
int	map_init(t_game *game, char **argv);
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
int	validate_map(t_list *map);
int	get_next_line(int fd, char **line);
void	free_data(t_dataset *set);
int	free_map(char **map, int index);
int	leave_game(t_dataset *set);
int	process_key(int key, t_dataset *set);
int	game_loop(t_dataset *set);
int	get_pixel(t_img *t_img, int s_x, int s_y);
void	put_pixel(t_img *data, int x, int y, unsigned int color);
int	ft_str_cons_only(char *str, char ch);
int	check_map_content(t_list *map);
int	process_key_pressed(int key, t_dataset *set);
void movement_processor(t_dataset *set);
int process_key_released(int key, t_dataset *set);






#endif
