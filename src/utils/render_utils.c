/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:51 by sergey            #+#    #+#             */
/*   Updated: 2022/03/06 01:10:35 by Sergey           ###   ########.fr       */
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
		return (&rend->wall);
	return (&rend->wall);
}

static int	render_image(t_dataset *set)
{
	/* player`s position vector*/
//	double posX = set->game->hero_pos.x, posY = set->game->hero_pos.y;
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
		int side; //was a NS or a EW wall hit?

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
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if((set->game->map)[mapX][mapY] == '1') hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(side == 0) wall_distance = (sideDistX - deltaDistX);
		else wall_distance = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screen_height / wall_distance);


		int pitch = 100;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screen_height / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + screen_height / 2;
		if(drawEnd >= screen_height) drawEnd = screen_height - 1;

		//texturing calculations
//		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0)
			wallX = posY + wall_distance * rayDirY;
		else
			wallX = posX + wall_distance * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int) (wallX * (double) texWidth);
		if(side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - (double)screen_height / 2 + (double)lineHeight / 2) * step;

			for(int y = 0; y < screen_height; y++)
			{
				if (y >= drawStart && y <= drawEnd)
				{
					// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
					int texY = (int) texPos & (texHeight - 1);
					texPos += step;
					uint32_t color = get_pixel(&set->rend->wall, texX, texY);
					//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
					if (side == 1) color = (color >> 1) & 8355711;
					put_pixel(&set->rend->main_img, x, y, color);
				} else
				{
					put_pixel(&set->rend->main_img, x, y, BLACK);
				}
			}
	}


	mlx_put_image_to_window(set->rend->mlx, set->rend->win, (set->rend->main_img.img), 0, 0);

//	//timing for input and FPS counter
//	oldTime = time;
//	time = getTicks();
//	double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
//	print(1.0 / frameTime); //FPS counter
//	redraw();

	//speed modifiers
//	double moveSpeed = 100 * 5.0; //the constant value is in squares/second
//	double rotSpeed = 100 * 3.0; //the constant value is in radians/second
//
//	readKeys();
//	//move forward if no wall in front of you
//	if(keyDown(SDLK_UP))
//	{
//		if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
//		if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
//	}
//	//move backwards if no wall behind you
//	if(keyDown(SDLK_DOWN))
//	{
//		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
//		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
//	}
//	//rotate to the right
//	if(keyDown(SDLK_RIGHT))
//	{
//		//both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
//		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
//		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
//	}
//	//rotate to the left
//	if(keyDown(SDLK_LEFT))
//	{		return (&rend->wall);

//		//both camera direction and camera plane must be rotated
//		double oldDirX = dirX;
//		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//		double oldPlaneX = planeX;
//		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//	}
//	if(keyDown(SDLK_ESCAPE))
//	{
//		break;
//	}
	return (1);
}

int	game_loop(t_dataset *set)
{
	t_rend	*r;

	(void) set;
	r = set->rend;
	render_image(set);
	if (set->game->win)
		leave_game(set);
	return (1);
}
