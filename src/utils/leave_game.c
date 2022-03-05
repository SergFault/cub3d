/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:43:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/05 17:43:56 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	leave_game(t_dataset *set)
{
	free_data(set);
	free_map(set->game->map, set->game->map_height);
	exit(0);
}