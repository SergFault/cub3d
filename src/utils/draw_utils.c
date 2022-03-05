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

void	put_pixel(t_img *data, int x, int y, unsigned int color)
{
	char	*dst;

	if (color != TRANSPARENCY)
	{
		dst = data->address + (y * data->line_length + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}


int	get_pixel(t_img *t_img, int s_x, int s_y)
{
	return (*(int *)(t_img->address + (s_y * t_img->line_length + s_x
			 * (t_img->bpp / 8))));
}

//void	img_on_img(t_img *img, t_img *s_img, int startX, int startY)
//{
//	t_draw_data	draw;
//
//	draw.x = 0;
//	while (draw.x < MODEL_SIZE)
//	{
//		draw.y = 0;
//		while (draw.y < MODEL_SIZE)
//		{
//			draw.off_x = (float)draw.x / (float)MODEL_SIZE;
//			draw.off_y = (float)draw.y / (float)MODEL_SIZE;
//			draw.s_x = draw.off_x * s_img->width;
//			draw.s_y = draw.off_y * s_img->height;
//			draw.color = get_pixel(s_img, draw.s_x, draw.s_y);
//			draw.d_x = startX + draw.x;
//			draw.d_y = startY + draw.y;
//			put_pixel(img, draw.d_x, draw.d_y, draw.color);
//			draw.y++;
//		}
//		draw.x++;
//	}
//}
