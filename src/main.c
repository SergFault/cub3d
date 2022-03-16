#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

int worldMap[mapWidth][mapHeight]=
		{
				{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
				{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
				{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
				{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
				{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
				{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
				{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
				{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
				{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
				{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
				{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
				{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
				{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
				{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
				{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
				{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};

static int	init_model(void *mlx, t_img img[10], char *path)
{
	img[0].img = mlx_png_file_to_image(mlx, "./textures/0.png", &(img[0].width),
									 & (img[0].height));
	img[0].address = mlx_get_data_addr(img[0].img, &img[0].bpp,
									 &img[0].line_length,
									 &img[0].endian);
	img[1].img = mlx_png_file_to_image(mlx, "./textures/1.png", &(img[1].width),
		& (img[1].height));
	img[1].address = mlx_get_data_addr(img[1].img, &img[1].bpp,
		&img[1].line_length,
		&img[1].endian);
	img[2].img = mlx_png_file_to_image(mlx, "./textures/2.png", &(img[2].width),
		& (img[2].height));
	img[2].address = mlx_get_data_addr(img[2].img, &img[2].bpp,
		&img[2].line_length,
		&img[2].endian);
	img[3].img = mlx_png_file_to_image(mlx, "./textures/3.png", &(img[3].width),
		& (img[3].height));
	img[3].address = mlx_get_data_addr(img[3].img, &img[3].bpp,
		&img[3].line_length,
		&img[3].endian);
	img[4].img = mlx_png_file_to_image(mlx, "./textures/4.png", &(img[4].width),
		& (img[4].height));
	img[4].address = mlx_get_data_addr(img[4].img, &img[4].bpp,
		&img[4].line_length,
		&img[4].endian);
	img[5].img = mlx_png_file_to_image(mlx, "./textures/5.png", &(img[5].width),
		& (img[5].height));
	img[5].address = mlx_get_data_addr(img[5].img, &img[5].bpp,
		&img[5].line_length,
		&img[5].endian);
	img[6].img = mlx_png_file_to_image(mlx, "./textures/6.png", &(img[6].width),
		& (img[6].height));
	img[6].address = mlx_get_data_addr(img[6].img, &img[6].bpp,
		&img[6].line_length,
		&img[6].endian);
	img[7].img = mlx_png_file_to_image(mlx, "./textures/7.png", &(img[7].width),
		& (img[7].height));
	img[7].address = mlx_get_data_addr(img[7].img, &img[7].bpp,
		&img[7].line_length,
		&img[7].endian);
	img[8].img = mlx_png_file_to_image(mlx, "./textures/8.png", &(img[8].width),
		& (img[8].height));
	img[8].address = mlx_get_data_addr(img[8].img, &img[8].bpp,
		&img[8].line_length,
		&img[8].endian);
	img[9].img = mlx_png_file_to_image(mlx, "./textures/9.png", &(img[9].width),
		& (img[9].height));
	img[9].address = mlx_get_data_addr(img[9].img, &img[9].bpp,
		&img[9].line_length,
		&img[9].endian);
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
	init_model(rend->mlx, rend->wall, WALL_PATH);
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
		printf("set.game\n");
		set.rend = &rend;
		printf("set.rend\n");
		init(&set, argv);
		printf("init\n");
		mlx_hook(rend.win, 2, (1L << 0), process_key_pressed, &set);
		printf("mlx hook key pressed\n");
		mlx_hook(set.rend->win, 3, (1L << 1), process_key_released, &set);
		printf("mlx hook key released\n");
		mlx_hook(set.rend->win, 17, 1L << 17, &leave_game, &set);
		printf("mlx hook game exit\n");
		mlx_loop_hook(rend.mlx, game_loop, &set);
		mlx_loop(rend.mlx);
	}
	else
		ft_putstr_fd(ARGS_ERROR, 2);
}


