#include "cub3d.h"

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
	set->rend->fire.i = 0;
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
		mlx_loop_hook(rend.mlx, game_loop, &set);
		mlx_loop(rend.mlx);
	}
	else
		ft_putstr_fd(ARGS_ERROR, 2);
	return (0);
}
