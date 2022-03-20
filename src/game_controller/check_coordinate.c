/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:43:36 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/20 18:45:39 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_x_coordinate(t_dataset *set, double coordinate)
{
	if (set->game->map[(int)set->game->hero_pos.y][(int)(coordinate)] != '1')
		return (1);
	return (0);
}

int	check_y_coordinate(t_dataset *set, double coordinate)
{
	if (set->game->map[(int)(coordinate)][(int)set->game->hero_pos.x] != '1')
		return (1);
	return (0);
}
