
#include <stdio.h>
#include "cub3d.h"

int check_x_coordinate(t_dataset *set, double coordinate)
{

	if (set->game->map[(int)set->game->hero_pos.y][(int)(coordinate)] != '1')
		return (1);
	return (0);
}

int check_y_coordinate(t_dataset *set, double coordinate)
{
	if (set->game->map[(int)(coordinate)][(int)set->game->hero_pos.x] != '1')
		return (1);
	return (0);
}

void movement_processor(t_dataset *set)
{
	double *pos_x;
	double *pos_y;
	double pos_x_check;
	double pos_y_check;
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
		pos_x_check = *pos_x + *dir_x * MV_SPEED;
		pos_y_check = *pos_y + *dir_y * MV_SPEED;
		if (check_x_coordinate(set, pos_x_check))
			*pos_x = pos_x_check;
		if (check_y_coordinate(set, pos_y_check))
			*pos_y = pos_y_check;
	}
	if (set->game->hero_pos.move_back)
	{
		pos_x_check = *pos_x - *dir_x * MV_SPEED;
		pos_y_check = *pos_y - *dir_y * MV_SPEED;
		if (check_x_coordinate(set, pos_x_check))
			*pos_x = pos_x_check;
		if (check_y_coordinate(set, pos_y_check))
			*pos_y = pos_y_check;
	}
	if (set->game->hero_pos.move_left)
	{
		pos_x_check = *pos_x + (*dir_x * cos(-M_PI_2) - *dir_y * sin(-M_PI_2))  * MV_SPEED;
		pos_y_check = *pos_y + (*dir_x * sin(-M_PI_2) + *dir_y * cos(-M_PI_2)) * MV_SPEED;
		if (check_x_coordinate(set, pos_x_check))
			*pos_x = pos_x_check;
		if (check_y_coordinate(set, pos_y_check))
			*pos_y = pos_y_check;
	}
	if (set->game->hero_pos.move_right)
	{
		pos_x_check = *pos_x + (*dir_x * cos(M_PI_2) - *dir_y * sin(M_PI_2))  * MV_SPEED;
		pos_y_check = *pos_y + (*dir_x * sin(M_PI_2) + *dir_y * cos(M_PI_2)) * MV_SPEED;
		if (check_x_coordinate(set, pos_x_check))
			*pos_x = pos_x_check;
		if (check_y_coordinate(set, pos_y_check))
			*pos_y = pos_y_check;
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