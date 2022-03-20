/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:40:26 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 21:01:25 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coordinates empty_coordinates(void)
{
	t_coordinates coordinates;

	coordinates.x = 0;
	coordinates.y = 0.5;
	coordinates.dir_x = 0;
	coordinates.dir_y = 0;
	coordinates.cam_plane_x = 0;
	coordinates.cam_plane_y = 0;
	coordinates.move_front = 0;
	coordinates.move_back = 0;
	coordinates.move_right = 0;
	coordinates.move_left = 0;
	coordinates.turn_left = 0;
	coordinates.turn_right = 0;
	return coordinates;
}

t_coordinates define_position(char ch, t_coordinates coor)
{
	if (ch == 'E')
	{
		coor.dir_x = 1;
		coor.dir_y = 0;
		coor.cam_plane_x = 0;
		coor.cam_plane_y = 1;
	}
	if (ch == 'W')
	{
		coor.dir_x = -1;
		coor.dir_y = 0;
		coor.cam_plane_x = 0;
		coor.cam_plane_y = -1;
	}
	if (ch == 'N')
	{
		coor.dir_x = 0;
		coor.dir_y = -1;
		coor.cam_plane_x = 1;
		coor.cam_plane_y = 0;
	}
	if (ch == 'S')
	{
		coor.dir_x = 0;
		coor.dir_y = 1;
		coor.cam_plane_x = -1;
		coor.cam_plane_y = 0;
	}
	//coor.x += 0.5;
	//coor.y += 0.5;
	return coor;
}

t_coordinates get_pos(t_game *game)
{
	t_coordinates pos;

	pos = empty_coordinates();
	while (pos.y < game->map_height)
	{
		pos.x = 0.5;
		while (pos.x < game->map_width)
		{
			if ((game->map[(int) pos.y][(int) pos.x] == 'E')
					|| (game->map[(int) pos.y][(int) pos.x] == 'W')
					|| (game->map[(int) pos.y][(int) pos.x] == 'S')
					|| (game->map[(int) pos.y][(int) pos.x] == 'N'))
				return (define_position(game->map[(int) pos.y][(int) pos.x], pos));
			pos.x++;
		}
		pos.y++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}