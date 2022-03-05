/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:42 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:27:42 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_dataset *set)
{
	int	cnt;

	cnt = 0;
	while (cnt < set->game->map_height)
	{
		free(set->game->map[cnt++]);
	}
	free(set->game->map);
	set->game->map = NULL;
}

void	free_env_obj(void *obj)
{
	free(obj);
}

int	free_map(char **map, int index)
{
	int	c;

	c = 0;
	if (!map)
		return (0);
	while (c < index)
	{
		free(map[c]);
		c++;
	}
	free(map);
	return (1);
}
