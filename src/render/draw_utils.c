/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:21 by sergey            #+#    #+#             */
/*   Updated: 2022/03/06 00:19:09 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	convert_rgb(const int rgb[3])
{
	unsigned int	color;

	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (color);
}

unsigned int	calc_shadows(unsigned int color, int y, double k[256])
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			intensity;
	int				index;

	r = (color & 0x00FF0000) >> 16;
	g = (color & 0x0000FF00) >> 8;
	b = color & 0x000000FF;
	if (y >= screen_height / 2)
	{
		intensity = k[255 - (int)((screen_height - y) / ((double)screen_height / 2 /
					  256))];
		r = r * intensity;
		g = g * intensity;
		b = b * intensity;
	}
	else
	{
		intensity = k[255 - (int)(y / ((double)screen_height / 2 / 256))];
		r = r * intensity;
		g = g * intensity;
		b = b * intensity;
	}
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	put_pixel(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->address + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}


int	get_pixel(t_img *t_img, int s_x, int s_y)
{
	return (*(int *)(t_img->address + (s_y * t_img->line_length + s_x
			 * (t_img->bpp / 8))));
}

void	fill_minimap(t_img	*minimap, t_game *game)
{
	int	x;
	int y;
	int	i;
	int	j;

	y = 0;
	while (y < game->map_height * 8)
	{
		x = 0;
		while (x < game->map_width * 8)
		{
			put_pixel(minimap, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '1' && game->map[y][x] != ' ')
			{
				i = 0;
				while (i < 8)
				{
					j = 0;
					while (j < 8)
						put_pixel(minimap, x * 8 + i, y * 8 + j++, 0xBBFFFFFF);
					i++;
				}
			}
			x++;
		}
		y++;
	}
}

void	fill_bg_img(t_dataset *set)
{
	int	x;
	int y;

	y = 0;
	while (y < screen_height)
	{
		x = 0;
		while (x < screen_width)
		{
			if (y >= screen_height / 2)
				put_pixel(&set->rend->back_img, x, y, //set->floor_color);
					calc_shadows(set->floor_color, y, set->k));
			else
				put_pixel(&set->rend->back_img, x, y, //set->ceiling_color);
					calc_shadows(set->ceiling_color, y, set->k));
			x++;
		}
		y++;
	}
	fill_minimap(&set->rend->minimap, set->game);
	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
			put_pixel(&set->game->hero, x, y++, 0x0000FF00);
		x++;
	}
}
