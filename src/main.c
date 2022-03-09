#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"


static int	init_model(void *mlx, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &(img->width),
									 & (img->height));
	img->address = mlx_get_data_addr(img->img, &img->bpp,
									 &img->line_length,
									 &img->endian);
	return (1);
}

static int	rend_init(t_rend *rend, t_game *game)
{
	rend->mlx = mlx_init();
	rend->win = mlx_new_window(rend->mlx, screen_width,
							   screen_height, "cub3d");
	rend->main_img.img = mlx_new_image(rend->mlx, screen_width,
									   screen_height);
	rend->main_img.address = mlx_get_data_addr(rend->main_img.img,
											   &rend->main_img.bpp,
											   &rend->main_img.line_length,
											   &rend->main_img.endian);
	init_model(rend->mlx, &rend->west, "textures/redbrick.xpm");
	init_model(rend->mlx, &rend->east, "textures/eagle.xpm");
	init_model(rend->mlx, &rend->north, "textures/stone.xpm");
	init_model(rend->mlx, &rend->south, "textures/wood.xpm");

	return (1);
}

static int	init(t_dataset *set, char **argv)
{
	init_data(set);
	map_init(set->game, argv);
	rend_init(set->rend, set->game);
	game_init(set->game);
	return (1);
}

int prt()
{
	printf("prnt\n");
}

int		main(int argc, char **argv)
{
	t_rend		rend;
	t_game		game;
	t_dataset	set;

	void *mlx;
	void *win;
	void *img;
	int img_width;
	int img_height;

	(void) argv;
	if (argc == 2)
	{
		set.game = &game;
		set.rend = &rend;
		init(&set, argv);
		mlx_hook(rend.win, 2, (1L << 0), process_key_pressed, &set);
		mlx_hook(set.rend->win, 3, (1L << 1), process_key_released, &set);
		mlx_hook(set.rend->win, 33, 0, &leave_game, &set);
		mlx_loop_hook(rend.mlx, game_loop, &set);
		mlx_loop(rend.mlx);
	}
	else
		ft_putstr_fd(ARGS_ERROR, 2);
}


