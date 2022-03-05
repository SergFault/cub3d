/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:11 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:27:11 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	cnt_map_content(t_list *map, t_objs_number *objs)
{
	char	*line;

	while (map)
	{
		line = (char *)map->content;
		while (*line)
		{
				//todo check content
			line++;
		}
		map = map->next;
	}
	return (1);
}

int	check_map_content(t_list *map)
{
	t_objs_number	objs;

	objs.player = 0;
	objs.collectable = 0;
	objs.exit = 0;
	cnt_map_content(map, &objs);
//	if ((objs.exit < 1) || (objs.collectable < 1) || (objs.player != 1)) //todo chec content
//		return (0);
	return (1);
}
