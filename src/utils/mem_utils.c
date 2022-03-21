/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:42 by sergey            #+#    #+#             */
/*   Updated: 2022/03/17 19:41:30 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_paths(t_dataset *set)
{
	free(set->path_east);
	free(set->path_west);
	free(set->path_north);
	free(set->path_south);
}

void	free_data(t_dataset *set)
{
	int	cnt;

	cnt = 0;
	while (cnt < set->game->map_h)
	{
		free(set->game->map[cnt++]);
	}
	free(set->game->map);
	set->game->map = NULL;
}

int	free_map(char **map)
{
	int	c;

	c = 0;
	if (!map)
		return (0);
	while (map[c])
	{
		free(map[c]);
		c++;
	}
	free(map);
	return (1);
}
