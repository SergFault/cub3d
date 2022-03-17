/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_skip_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:33:00 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 19:39:11 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_texture_path(t_list *line, int *have_size, t_dataset *set)
{
	char *line_str;

	line_str = (char *)(line->content);
	if (line_str[0] == '\0')
		return (1);
	if (ft_strncmp(line_str, "NO ", 3)  == 0)
	{
		have_size[NORTH_SIDE] = 1;
		free(set->path_north);
		set->path_north = ft_strdup(line_str + 3);
		return (1);
	}
	else if (ft_strncmp(line_str, "SO ", 3)  == 0)
	{
		have_size[SOUTH_SIDE] = 1;
		free(set->path_south);
		set->path_south = ft_strdup(line_str + 3);
		return (1);
	}
	else if (ft_strncmp(line_str, "WE ", 3) == 0)
	{
		have_size[WEST_SIDE] = 1;
		free(set->path_west);
		set->path_west = ft_strdup(line_str + 3);
		return (1);
	}
	else if (ft_strncmp(line_str, "EA ", 3)  == 0)
	{
		have_size[EAST_SIDE] = 1;
		free(set->path_east);
		set->path_east = ft_strdup(line_str + 3);
		return (1);
	}
	return (0);
}

static int have_all_sides(int sides[4])
{
	if (sides[0] && sides[1] && sides[2] && sides[3])
		return (1);
	return (0);
}

int check_n_skip_textures(t_list **list, t_dataset *set)
{
	int sides[4];

	arr_to_zero(sides, 4);
	while(*list && is_texture_path(*list, sides, set))
		*list = (*list)->next;
	if (have_all_sides(sides))
		return (1);
	return (0);
}
