/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:31 by sergey            #+#    #+#             */
/*   Updated: 2022/03/06 01:26:24 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int process_key(int key, t_dataset *set)
{
	double *pos_x;
	double *pos_y;
	double *dir_x;
	double *dir_y;
	double *plane_x;
	double *plane_y;
	char	**map;

	pos_x = &set->game->hero_pos.x;
	pos_y = &set->game->hero_pos.y;
	dir_x = &set->game->hero_pos.dir_x;
	dir_y = &set->game->hero_pos.dir_y;
	plane_x = &set->game->hero_pos.cam_plane_x;
	plane_y  = &set->game->hero_pos.cam_plane_y;
	map = set->game->map;

	(void) set;
	if (key == ESC)
		leave_game(set);
	if (key == UP)
	{
		*pos_x += *dir_x * MV_SPEED;
		*pos_y += *dir_y * MV_SPEED;
	}
	if (key == DOWN)
	{
		printf("sada\n");
		*pos_x -= *dir_x * MV_SPEED;
		*pos_y -= *dir_y * MV_SPEED;
	}
	if (key == LEFT)
		printf("Move left\n");
	if (key == RIGHT)
	{
		double oldDirX = *dir_x;
		*dir_x = *dir_x * cos(-RT_SPEED) - *dir_y * sin(-RT_SPEED);
		*dir_y = oldDirX * sin(-RT_SPEED) + *dir_y * cos(-RT_SPEED);
		double oldPlaneX = *plane_x;
		*plane_x = *plane_x * cos(-RT_SPEED) - *plane_y * sin(-RT_SPEED);
		*plane_y = oldPlaneX * sin(-RT_SPEED) + *plane_y * cos(-RT_SPEED);

//		double oldDirX = dirX;
//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	return (0);
}
