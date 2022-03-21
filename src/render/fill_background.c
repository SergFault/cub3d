/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:40 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 19:20:09 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	calc_shadows(unsigned int color, int y, const double k[256])
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			intensity;

	r = (color & 0x00FF0000) >> 16;
	g = (color & 0x0000FF00) >> 8;
	b = color & 0x000000FF;
	if (y >= H_RES / 2)
	{
		intensity = k[255 - (int)((H_RES - y)
				/ ((double)H_RES / 2 / 256))];
		r = r * intensity;
		g = g * intensity;
		b = b * intensity;
	}
	else
	{
		intensity = k[255 - (int)(y / ((double)H_RES / 2 / 256))];
		r = r * intensity;
		g = g * intensity;
		b = b * intensity;
	}
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static void	fill_minimap(t_img	*minimap, t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (game->map[y][x])
		{
			i = 0;
			while (i < 8)
			{
				j = 0;
				while (j < 8)
					put_pixel(minimap, x * 8 + i, y * 8 + j++, 0x00FF0000
						* ((game->map[y][x] != '1' && game->map[y][x] != ' ')));
				i++;
			}
			x++;
		}
		y++;
	}
}

static void	fill_hero(t_dataset *set)
{
	int	x;
	int	y;

	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
			put_pixel(&set->game->hero, x, y++, 0x0000FF00);
		x++;
	}
}

void	fill_bg_img(t_dataset *set)
{
	int	x;
	int	y;

	y = 0;
	while (y < H_RES)
	{
		x = 0;
		while (x < W_RES)
		{
			if (y >= H_RES / 2)
				put_pixel(&set->rend->back_img, x, y,
					calc_shadows(set->floor_color, y, set->k));
			else
				put_pixel(&set->rend->back_img, x, y,
					calc_shadows(set->ceiling_color, y, set->k));
			x++;
		}
		y++;
	}
	fill_minimap(&set->rend->minimap, set->game);
	fill_hero(set);
}
