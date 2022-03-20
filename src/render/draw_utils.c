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

void	put_pixel(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->address + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_img *t_img, int s_x, int s_y)
{
	return (*(int *)(t_img->address + (s_y * t_img->line_length
			+ s_x * (t_img->bpp / 8))));
}

unsigned int	shadows(unsigned int color, double y)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	double			intensity;

	r = (color & 0x00FF0000) >> 16;
	g = (color & 0x0000FF00) >> 8;
	b = color & 0x000000FF;
	intensity = 1 / y * 2;
	if (intensity > 1.0)
		intensity = 1.0;
	r = r * intensity;
	g = g * intensity;
	b = b * intensity;
	color = (r << 16) | (g << 8) | b;
	return (color);
}
