#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"


static int	init_model(void *mlx, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &(img->width),
									 & (img->height));
	if (!img->img)
		return ((int) ft_error_null(TEXTURES_INIT_ERROR));
	img->address = mlx_get_data_addr(img->img, &img->bpp,
									 &img->line_length,
									 &img->endian);
	return (1);
}

static int	rend_init(t_dataset *set)
{
	set->rend->mlx = mlx_init();
	set->rend->win = mlx_new_window(set->rend->mlx, screen_width,
							   screen_height, "cub3d");
	set->rend->main_img.img = mlx_new_image(set->rend->mlx, screen_width,
									   screen_height);
	set->rend->main_img.address = mlx_get_data_addr(set->rend->main_img.img,
											   &set->rend->main_img.bpp,
											   &set->rend->main_img.line_length,
											   &set->rend->main_img.endian);
	if(!init_model(set->rend->mlx, &set->rend->west, set->path_west)
		|| !init_model(set->rend->mlx, &set->rend->east, set->path_east)
		|| !init_model(set->rend->mlx, &set->rend->north, set->path_north)
		|| !init_model(set->rend->mlx, &set->rend->south, set->path_south))
		return (0);
	return (1);
}

static int	init(t_dataset *set, char *argv)
{
	init_data(set);
	map_init(set, argv);
	if (!rend_init(set))
		leave_game(set);
	game_init(set->game);
	return (1);
}

int		main(int argc, char **argv)
{
	t_rend		rend;
	t_game		game;
	t_dataset	set;

	(void) argv;
	if (argc == 2)
	{
		set.game = &game;
		set.rend = &rend;
		init(&set, argv[1]);
		mlx_hook(rend.win, 2, (1L << 0), process_key_pressed, &set);
		mlx_hook(set.rend->win, 3, (1L << 1), process_key_released, &set);
		mlx_hook(set.rend->win, 33, 0, &leave_game, &set);
		mlx_loop_hook(rend.mlx, game_loop, &set);
		mlx_loop(rend.mlx);
	}
	else
		ft_putstr_fd(ARGS_ERROR, 2);
}
