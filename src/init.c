/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:27 by sergey            #+#    #+#             */
/*   Updated: 2022/03/09 13:41:41 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "cub3d.h"

void set_img_null(t_img img[10])
{
	int i;

	i = 0;
	while (i < 10)
	{
		img[i].img = NULL;
		img[i].address = NULL;
		img[i].bpp = 0;
		img[i].line_length = 0;
		img[i].endian = 0;
		img[i].width = 0;
		img[i].height = 0;
		i++;
	}
}

void init_data(t_dataset *set)
{
	set->rend->mlx = NULL;
	set->rend->win = NULL;
	set_img_null(set->rend->wall);
	set->rend->i = 0;
	set->game->map_width = 0;
	set->game->map_height = 0;
	set->game->map = NULL;
}

void game_init(t_game *game)
{
	game->hero_pos.move_front = 0;
	game->hero_pos.move_back = 0;
	game->hero_pos.move_right = 0;
	game->hero_pos.move_left = 0;
	game->hero_pos.turn_left = 0;
	game->hero_pos.turn_right = 0;

	game->hero_pos.x = 5.0;
	game->hero_pos.y = 5.0;
	game->hero_pos.dir_x = -1.0;
	game->hero_pos.dir_y = 0.0;
	game->hero_pos.cam_plane_x = 0.0;
	game->hero_pos.cam_plane_y = -1.0;
	game->win = 0;
}
