/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:27 by sergey            #+#    #+#             */
/*   Updated: 2022/03/06 00:52:50 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "cub3d.h"

void	set_img_null(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_data(t_dataset *set)
{
	set->rend->mlx = NULL;
	set->rend->win = NULL;
	set_img_null(&set->rend->wall);
	set->game->map_width = 0;
	set->game->map_height = 0;
	set->game->map = NULL;
}

void	game_init(t_game *game)
{
	game->hero_pos.x = 3.0;
	game->hero_pos.y = 3.0;
	game->hero_pos.dir_x = -1.0;
	game->hero_pos.dir_y = 0.0;
	game->hero_pos.cam_plane_x = 0.0;
	game->hero_pos.cam_plane_y = -1.0;
	game->win = 0;
}
