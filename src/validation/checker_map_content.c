/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:11 by sergey            #+#    #+#             */
/*   Updated: 2022/03/17 14:44:24 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cnt_map_content(char **map, t_objs_number *objs)
{
	char	*line;

	while (*map)
	{
		line = (char *)(*map);
		while (*line)
		{
			if (*line == 'N' || *line == 'W' || *line == 'E' || *line == 'S')
				objs->player++;
			line++;
		}
		map++;
	}
	return (1);
}

int	check_map_content(char **map)
{
	t_objs_number	objs;

	objs.player = 0;
	cnt_map_content(map, &objs);
	if (objs.player != 1)
		return (0);
	return (1);
}
