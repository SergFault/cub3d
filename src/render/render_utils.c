/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:51 by sergey            #+#    #+#             */
/*   Updated: 2022/03/09 20:00:40 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <bits/stdint-uintn.h>
#include "cub3d.h"
#include "mlx.h"
#include <sys/time.h>


t_img	*get_img(t_rend *rend, char ch)
{
	if (ch == WALL_CH)
		return (&rend->east);
	return (&rend->east);
}

static int	render_image(t_dataset *set)
{
	/* player`s position vector*/
	double posX = set->game->hero_pos.x, posY = set->game->hero_pos.y;


	struct timeval stop, start;

	/* player`s direction vector*/
	double dirX = set->game->hero_pos.dir_x, dirY = set->game->hero_pos.dir_y;
	/* camera`s plane vector */
	double planeX = set->game->hero_pos.cam_plane_x, planeY = set->game->hero_pos.cam_plane_y;

	t_img *picture = &set->rend->main_img;
	char *data_address = set->rend->main_img.address;

	for(int x = 0; x < screen_width; x++)
	{

		//calculate ray position and direction
		double cameraX = 2 * x / (double)screen_width - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX*cameraX;
		double rayDirY = dirY + planeY*cameraX;

		//which box of the map we're in
		int mapX = (int) posX;
		int mapY = (int) posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : ft_abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : ft_abs(1 / rayDirY);
		double wall_distance;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //wich side NSWE

		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		int x_texture;
		int y_texture;

		while (hit == 0)
		{
			if (rayDirY < 0)
				y_texture = NORTH_SIDE;
			else
				y_texture = SOUTH_SIDE;

			if (rayDirX > 0)
				x_texture = EAST_SIDE;
			else
				x_texture = WEST_SIDE;

			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = x_texture;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = y_texture;
			}
			//Check if ray has hit a wall
			if((set->game->map)[mapY][mapX] == '1')
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(side == x_texture) wall_distance = (sideDistX - deltaDistX);
		else wall_distance = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screen_height / wall_distance);


		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screen_height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screen_height / 2;
		if(drawEnd >= screen_height) drawEnd = screen_height - 1;


		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == x_texture)
			wallX = -(posY + wall_distance * rayDirY);
		else
			wallX = posX + wall_distance * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int) (wallX * (double) texWidth);
//		if((side == NORTH_SIDE || side == SOUTH_SIDE) && rayDirX > 0)
//			texX = texWidth - texX - 1;

//		if((side == EAST_SIDE || side == WEST_SIDE) && rayDirY < 0)
//			texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - (double)screen_height / 2 + (double)lineHeight / 2) * step;
		t_img *img;
		if (side == NORTH_SIDE)
			img = &set->rend->north;
		else if (side == WEST_SIDE)
			img = &set->rend->west;
		else if (side == EAST_SIDE)
			img = &set->rend->east;
		else
			img = &set->rend->south;

			for(int y = 0; y < screen_height; y++)
			{
				if (y >= drawStart && y <= drawEnd)
				{
					// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
					int texY = (int) texPos & (texHeight - 1);
					texPos += step;
					uint32_t color = get_pixel(img, texX, texY);
					put_pixel(&set->rend->main_img, x, y, color);
				}
				else
				{
					if (y >= screen_height / 2)
						put_pixel(&set->rend->main_img, x, y, set->floor_color);
					else
						put_pixel(&set->rend->main_img, x, y, set->ceiling_color);
				}
			}
	}
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, (set->rend->main_img.img), 0, 0);
	return (1);
}

int	game_loop(t_dataset *set)
{
	t_rend	*r;

	(void) set;
	movement_processor(set);
	render_image(set);
//	if (set->game->win)
//		leave_game(set);
	return (1);
}
