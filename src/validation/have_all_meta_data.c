/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_all_meta_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:22:31 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/20 12:23:04 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	have_all_meta_data(t_dataset *set)
{
	return ((set->path_south != NULL)
		&& (set->path_north != NULL)
		&& (set->path_west != NULL)
		&& (set->path_east != NULL)
		&& (set->ce_rgb[0] != -1)
		&& (set->fl_rgb[0] != -1));
}
