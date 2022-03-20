/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_processor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:47:12 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/20 19:17:17 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_dataset *set)
{
	double	pos_check[2];
	double	*pos[2];
	double	*dir[2];

	pos[X] = &set->game->hero_pos.x;
	pos[Y] = &set->game->hero_pos.y;
	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	pos_check[X] = *(pos[X]) + *(dir[X]) * MV_SPEED;
	pos_check[Y] = *(pos[Y]) + *(dir[Y]) * MV_SPEED;
	if (check_x_coordinate(set, pos_check[X]))
		*(pos[X]) = pos_check[X];
	if (check_y_coordinate(set, pos_check[Y]))
		*(pos[Y]) = pos_check[Y];
}

void	move_back(t_dataset *set)
{
	double	pos_check[2];
	double	*pos[2];
	double	*dir[2];

	pos[X] = &set->game->hero_pos.x;
	pos[Y] = &set->game->hero_pos.y;
	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	pos_check[X] = *(pos[X]) - *(dir[X]) * MV_SPEED;
	pos_check[Y] = *(pos[Y]) - *(dir[Y]) * MV_SPEED;
	if (check_x_coordinate(set, pos_check[X]))
		*(pos[X]) = pos_check[X];
	if (check_y_coordinate(set, pos_check[Y]))
		*(pos[Y]) = pos_check[Y];
}

void	move_left(t_dataset *set)
{
	double	pos_check[2];
	double	*pos[2];
	double	*dir[2];

	pos[X] = &set->game->hero_pos.x;
	pos[Y] = &set->game->hero_pos.y;
	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	pos_check[X] = *(pos[X]) + (*(dir[X]) * cos(-M_PI_2)
			- *(dir[Y]) * sin(-M_PI_2)) * MV_SPEED;
	pos_check[Y] = *(pos[Y]) + (*(dir[X]) * sin(-M_PI_2)
			+ *(dir[Y]) * cos(-M_PI_2)) * MV_SPEED;
	if (check_x_coordinate(set, pos_check[X]))
		*(pos[X]) = pos_check[X];
	if (check_y_coordinate(set, pos_check[Y]))
		*(pos[Y]) = pos_check[Y];
}

void	move_right(t_dataset *set)
{
	double	pos_check[2];
	double	*pos[2];
	double	*dir[2];

	pos[X] = &set->game->hero_pos.x;
	pos[Y] = &set->game->hero_pos.y;
	dir[X] = &set->game->hero_pos.dir_x;
	dir[Y] = &set->game->hero_pos.dir_y;
	pos_check[X] = *(pos[X]) + (*(dir[X]) * cos(M_PI_2)
			- *(dir[Y]) * sin(M_PI_2)) * MV_SPEED;
	pos_check[Y] = *(pos[Y]) + (*(dir[X]) * sin(M_PI_2)
			+ *(dir[Y]) * cos(M_PI_2)) * MV_SPEED;
	if (check_x_coordinate(set, pos_check[X]))
		*(pos[X]) = pos_check[X];
	if (check_y_coordinate(set, pos_check[Y]))
		*(pos[Y]) = pos_check[Y];
}
