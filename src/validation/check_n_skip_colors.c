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

void parse_colors(char *pattern, int *rgb)
{
	rgb[0] = ft_atoi(pattern);
	rgb[1] = ft_atoi(pattern + 4);
	rgb[2] = ft_atoi(pattern + 8);
}

int ft_is_color_data(t_list *line, int have_color[2], t_dataset *set)
{
	char *line_str;
	int rgb[3];

	arr_to_zero(rgb, 3);
	line_str = (char *) (line->content);
	if (line_str[0] == '\0')
		return (1);
	if (ft_strncmp(line_str, "F ", 2) == 0 &&
		is_valid_color_pattern(line_str + 2))
	{
		parse_colors(line_str + 2, rgb);
		have_color[HAVE_FLOOR] = YES;
		set_rgb_arr(rgb, set->floor_rgb);
		return (1);
	}
	else if (ft_strncmp(line_str, "C ", 2) == 0)
	{
		parse_colors(line_str + 2, rgb);
		have_color[HAVE_CEIL] = YES;
		set_rgb_arr(rgb, set->ceiling_rgb);
		return (1);
	}
	return (0);
}

static int have_all_colors(int sides[2])
{
	if (sides[0] && sides[1])
		return (1);
	return (0);
}

int check_n_skip_colors(t_list **list, t_dataset *set)
{
	int colors_complete_flag[2];

	arr_to_zero(colors_complete_flag, 2);
	while (*list && ft_is_color_data(*list, colors_complete_flag, set))
		*list = (*list)->next;
	if (have_all_colors(colors_complete_flag))
		return (1);
	return (0);
}
