/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:31 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 18:34:06 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_key_pressed(int key, t_dataset *set)
{
	if (key == ESC)
		leave_game(set);
	if (key == UP)
		set->game->hero_pos.move_front = 1;
	if (key == DOWN)
		set->game->hero_pos.move_back = 1;
	if (key == 123)
		set->game->hero_pos.turn_left = 1;
	if (key == 124)
		set->game->hero_pos.turn_right = 1;
	if (key == RIGHT)
		set->game->hero_pos.move_right = 1;
	if (key == LEFT)
		set->game->hero_pos.move_left = 1;
	return (0);
}

int	process_key_released(int key, t_dataset *set)
{
	if (key == ESC)
		leave_game(set);
	if (key == UP)
		set->game->hero_pos.move_front = 0;
	if (key == DOWN)
		set->game->hero_pos.move_back = 0;
	if (key == 123)
		set->game->hero_pos.turn_left = 0;
	if (key == 124)
		set->game->hero_pos.turn_right = 0;
	if (key == RIGHT)
		set->game->hero_pos.move_right = 0;
	if (key == LEFT)
		set->game->hero_pos.move_left = 0;
	return (0);
}

int		process_mouse(int x, int y, t_dataset *set)
{
	(void)y;
	if (x < (screen_width / 2 - 3))
	{
		//set->game->hero_pos.turn_right = 0;
		set->game->hero_pos.turn_left = 1;
	}
	else if (x > (screen_width / 2 + 3))
	{
		//set->game->hero_pos.turn_left = 0;
		set->game->hero_pos.turn_right = 1;
	}
	else
	{
		set->game->hero_pos.turn_left = 0;
		set->game->hero_pos.turn_right = 0;
	}
	mlx_mouse_move(set->rend->win, screen_width / 2, 0);
	return (0);
}
