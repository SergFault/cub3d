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

static int	parse_side_2(int side, t_list *line, t_dataset *set)
{
	char	*line_str;

	line_str = (char *)line->content;
	if (side == WEST_SIDE)
	{
		if (set->path_west != NULL)
			return (0);
		line_str += 3;
		skip_spaces(&line_str);
		set->path_west = ft_strdup(line_str);
	}
	else
	{
		if (set->path_east != NULL)
			return (0);
		line_str += 3;
		skip_spaces(&line_str);
		set->path_east = ft_strdup(line_str);
	}
	return (1);
}

static int	parse_side(int side, t_list *line, t_dataset *set)
{
	char	*line_str;

	line_str = (char *)line->content;
	if (side == SOUTH_SIDE)
	{
		if (set->path_south != NULL)
			return (0);
		line_str += 3;
		skip_spaces(&line_str);
		set->path_south = ft_strdup(line_str);
	}
	else if (side == NORTH_SIDE)
	{
		if (set->path_north != NULL)
			return (0);
		line_str += 3;
		skip_spaces(&line_str);
		set->path_north = ft_strdup(line_str);
	}
	else
		return (parse_side_2(side, line, set));
	return (1);
}

static int	parse_path(t_list *line, t_dataset *set)
{
	char	*line_str;

	line_str = (char *)(line->content);
	if (ft_strncmp(line_str, "NO ", 3) == 0)
	{
		return (parse_side(NORTH_SIDE, line, set));
	}
	else if (ft_strncmp(line_str, "SO ", 3) == 0)
	{
		return (parse_side(SOUTH_SIDE, line, set));
	}
	else if (ft_strncmp(line_str, "WE ", 3) == 0)
	{
		return (parse_side(WEST_SIDE, line, set));
	}
	else if (ft_strncmp(line_str, "EA ", 3) == 0)
	{
		return (parse_side(EAST_SIDE, line, set));
	}
	return (0);
}

int	check_n_skip_textures(t_list **list, t_dataset *set)
{
	if (parse_path(*list, set))
	{
		*list = (*list)->next;
		return (1);
	}
	return (0);
}
