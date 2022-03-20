/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_skip_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:33:00 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/15 19:21:42 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int thee_digits_check_skip(char **str)
{
	int i = 0;

	while (*str && ft_is_digit(**str) && i < 3)
	{
		(*str)++;
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

int comma_check_skip(char **str)
{
	if (*str && **str == ',')
	{
		(*str)++;
		return (1);
	}
	return (0);
}

static int is_valid_color_pattern(char *str)
{
	if (thee_digits_check_skip(&str)
		&& comma_check_skip(&str)
		&& thee_digits_check_skip(&str)
		&& comma_check_skip(&str)
		&& thee_digits_check_skip(&str)
		&& *str == '\0')
		return (1);
	return (0);
}

void skip_num_comma(char **pattern)
{
	while (*pattern && ft_is_digit(**pattern))
		(*pattern)++;
	if (*pattern && **pattern == ',')
		(*pattern)++;
}


int correct_colors(int color1, int color2, int color3)
{
	return ((color1 < 256 && color1 >=0)
			&& (color2 < 256 && color2 >=0)
			&& (color3 < 256 && color3 >=0));
}

int parse_colors(char *pattern, t_dataset *set, int side)
{
	if (side == CEIL)
	{
		if (set->ceiling_rgb[0] != -1)
			return (0);
		set->ceiling_rgb[0] = ft_atoi(pattern);
		skip_num_comma(&pattern);
		set->ceiling_rgb[1] = ft_atoi(pattern);
		skip_num_comma(&pattern);
		set->ceiling_rgb[2] = ft_atoi(pattern);
		if (!correct_colors(set->ceiling_rgb[0], set->ceiling_rgb[1], set->ceiling_rgb[2]))
			return (0);
	}
	if (side == FLOOR)
	{
		if (set->floor_rgb[0] != -1)
			return (0);
		set->floor_rgb[0] = ft_atoi(pattern);
		skip_num_comma(&pattern);
		set->floor_rgb[1] = ft_atoi(pattern);
		skip_num_comma(&pattern);
		set->floor_rgb[2] = ft_atoi(pattern);
		if (!correct_colors(set->floor_rgb[0], set->floor_rgb[1], set->floor_rgb[2]))
			return (0);
	}
	return (1);
}

static int parse_color_data(t_list *line, t_dataset *set)
{
	char *line_str;

	line_str = (char *) (line->content);
	if (line_str[0] == '\0')
		return (1);
	if (ft_strncmp(line_str, "F ", 2) == 0 &&
		is_valid_color_pattern(line_str + 2))
	{
		return parse_colors(line_str + 2, set, FLOOR);
	}
	else if (ft_strncmp(line_str, "C ", 2) == 0)
	{
		return parse_colors(line_str + 2, set, CEIL);
	}
	return (0);
}


int check_n_skip_colors(t_list **list, t_dataset *set)
{
	if (parse_color_data(*list, set))
	{
		*list = (*list)->next;
		set->floor_color = convert_rgb(set->floor_rgb);
		set->ceiling_color = convert_rgb(set->ceiling_rgb);
		return (1);
	}
	return (0);
}
