#include "cub3d.h"

int	init_fire(void *mlx, t_fire *fire)
{
	fire->i = 0;
	fire->img[0].img = mlx_png_file_to_image(mlx, "textures/fire/0000.png",
		&(fire->img[0].width), &(fire->img[0].height));
	fire->img[1].img = mlx_png_file_to_image(mlx, "textures/fire/0001.png",
		&(fire->img[1].width), &(fire->img[1].height));
	fire->img[2].img = mlx_png_file_to_image(mlx, "textures/fire/0002.png",
		&(fire->img[2].width), &(fire->img[2].height));
	fire->img[3].img = mlx_png_file_to_image(mlx, "textures/fire/0003.png",
		&(fire->img[3].width), &(fire->img[3].height));
	fire->img[4].img = mlx_png_file_to_image(mlx, "textures/fire/0004.png",
		&(fire->img[4].width), &(fire->img[4].height));
	fire->img[5].img = mlx_png_file_to_image(mlx, "textures/fire/0005.png",
		&(fire->img[5].width), &(fire->img[5].height));
	fire->img[6].img = mlx_png_file_to_image(mlx, "textures/fire/0006.png",
		&(fire->img[6].width), &(fire->img[6].height));
	fire->img[7].img = mlx_png_file_to_image(mlx, "textures/fire/0007.png",
		&(fire->img[7].width), &(fire->img[7].height));
	fire->img[8].img = mlx_png_file_to_image(mlx, "textures/fire/0008.png",
		&(fire->img[8].width), &(fire->img[8].height));
	fire->img[9].img = mlx_png_file_to_image(mlx, "textures/fire/0009.png",
		&(fire->img[9].width), &(fire->img[9].height));
	fire->img[10].img = mlx_png_file_to_image(mlx, "textures/fire/0010.png",
		&(fire->img[10].width), &(fire->img[10].height));
	fire->img[11].img = mlx_png_file_to_image(mlx, "textures/fire/0011.png",
		&(fire->img[11].width), &(fire->img[11].height));
	fire->img[12].img = mlx_png_file_to_image(mlx, "textures/fire/0012.png",
		&(fire->img[12].width), &(fire->img[12].height));
	fire->img[13].img = mlx_png_file_to_image(mlx, "textures/fire/0013.png",
		&(fire->img[13].width), &(fire->img[13].height));
	fire->img[14].img = mlx_png_file_to_image(mlx, "textures/fire/0014.png",
		&(fire->img[14].width), &(fire->img[14].height));
	fire->img[15].img = mlx_png_file_to_image(mlx, "textures/fire/0015.png",
		&(fire->img[15].width), &(fire->img[15].height));
	fire->img[16].img = mlx_png_file_to_image(mlx, "textures/fire/0016.png",
		&(fire->img[16].width), &(fire->img[16].height));
	fire->img[17].img = mlx_png_file_to_image(mlx, "textures/fire/0017.png",
		&(fire->img[17].width), &(fire->img[17].height));
	fire->img[18].img = mlx_png_file_to_image(mlx, "textures/fire/0018.png",
		&(fire->img[18].width), &(fire->img[18].height));
	fire->img[19].img = mlx_png_file_to_image(mlx, "textures/fire/0019.png",
		&(fire->img[19].width), &(fire->img[19].height));
}



static int	init(t_dataset *set, char *argv)
{
	init_data(set);
	map_init(set, argv);
	if (!(set->game->map))
	{
		free_textures_paths(set);
		ft_putstr_fd(MAP_VALID_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!rend_init(set))
		leave_game(set);
	fill_bg_img(set);
	set->game->hero_pos = get_pos(set->game);
	return (1);
}

int	main(int argc, char **argv)
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
		mlx_hook(set.rend->win, 17, 1L << 17, &leave_game, &set);
		mlx_mouse_hide();
		//mlx_hook(set.rend->win, 6, 0, process_mouse, &set);
		mlx_loop_hook(rend.mlx, game_loop, &set);
		mlx_loop(rend.mlx);
	}
	else
		ft_putstr_fd(ARGS_ERROR, 2);
	return (0);
}
