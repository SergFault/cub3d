
#include <stdio.h>
#include "cub3d.h"

void movement_processor(t_dataset *set)
{
	double *pos_x;
	double *pos_y;
	double *dir_x;
	double *dir_y;
	double *plane_x;
	double *plane_y;

	pos_x = &set->game->hero_pos.x;
	pos_y = &set->game->hero_pos.y;
	dir_x = &set->game->hero_pos.dir_x;
	dir_y = &set->game->hero_pos.dir_y;
	plane_x = &set->game->hero_pos.cam_plane_x;
	plane_y  = &set->game->hero_pos.cam_plane_y;

	if (set->game->hero_pos.move_front)
	{
		*pos_x += *dir_x * MV_SPEED;
		*pos_y += *dir_y * MV_SPEED;
	}
	if (set->game->hero_pos.move_back)
	{
		*pos_x -= *dir_x * MV_SPEED;
		*pos_y -= *dir_y * MV_SPEED;
	}
	if (set->game->hero_pos.turn_left)
	{
		double oldDirX = *dir_x;
		*dir_x = *dir_x * cos(-RT_SPEED) - *dir_y * sin(-RT_SPEED);
		*dir_y = oldDirX * sin(-RT_SPEED) + *dir_y * cos(-RT_SPEED);
		double oldPlaneX = *plane_x;
		*plane_x = *plane_x * cos(-RT_SPEED) - *plane_y * sin(-RT_SPEED);
		*plane_y = oldPlaneX * sin(-RT_SPEED) + *plane_y * cos(-RT_SPEED);
	}
	if (set->game->hero_pos.turn_right)
	{
		double oldDirX = *dir_x;
		*dir_x = *dir_x * cos(RT_SPEED) - *dir_y * sin(RT_SPEED);
		*dir_y = oldDirX * sin(RT_SPEED) + *dir_y * cos(RT_SPEED);
		double oldPlaneX = *plane_x;
		*plane_x = *plane_x * cos(RT_SPEED) - *plane_y * sin(RT_SPEED);
		*plane_y = oldPlaneX * sin(RT_SPEED) + *plane_y * cos(RT_SPEED);
	}
}