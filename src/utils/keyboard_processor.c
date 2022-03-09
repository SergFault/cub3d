/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:31 by sergey            #+#    #+#             */
/*   Updated: 2022/03/09 13:21:28 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int process_key_pressed(int key, t_dataset *set)
{
	(void) set;

	if (key == ESC)
		leave_game(set);
	if (key == UP)
	{
		printf("move_front\n");
		set->game->hero_pos.move_front = 1;
	}
	if (key == DOWN)
	{
		set->game->hero_pos.move_back = 1;

	}
	if (key == LEFT)
	{
		printf("move_left\n");
		set->game->hero_pos.turn_left = 1;
	}
	if (key == RIGHT)
	{
		set->game->hero_pos.turn_right = 1;
	}
	return (0);
}

int process_key_released(int key, t_dataset *set)
{
	(void) set;
	if (key == ESC)
		leave_game(set);
	if (key == UP)
	{
		set->game->hero_pos.move_front = 0;
	}
	if (key == DOWN)
	{
		set->game->hero_pos.move_back = 0;
	}
	if (key == LEFT)
		set->game->hero_pos.turn_left = 0;
	if (key == RIGHT)
	{
		set->game->hero_pos.turn_right = 0;
	}
	return (0);
}
