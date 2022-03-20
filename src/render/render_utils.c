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

#include "cub3d.h"

static int	render_image(t_dataset *set)
{
	int	i;
	/* player`s position vector*/
	double posX = set->game->hero_pos.x, posY = set->game->hero_pos.y;


	struct timeval stop, start;

	/* player`s direction vector*/
	double dirX = set->game->hero_pos.dir_x, dirY = set->game->hero_pos.dir_y;
	/* camera`s plane vector */
	double planeX = set->game->hero_pos.cam_plane_x, planeY = set->game->hero_pos.cam_plane_y;

	t_img *picture = &set->rend->main_img;
	char *data_address = set->rend->main_img.address;

	for(int x = 0; x < W_RES; x++)
	{

		//calculate ray position and direction
		double cameraX = 2 * x / (double)W_RES - 1; //x-coordinate in camera space
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
		int lineHeight = (int)(H_RES / wall_distance);


		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + H_RES / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + H_RES / 2;
		if(drawEnd >= H_RES) drawEnd = H_RES - 1;


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
		double texPos = (drawStart - (double)H_RES / 2 + (double)lineHeight / 2) * step;
		t_img *img;
		if (side == NORTH_SIDE)
			img = &set->rend->north;
		else if (side == WEST_SIDE)
			img = &set->rend->west;
		else if (side == EAST_SIDE)
			img = &set->rend->east;
		else
			img = &set->rend->south;

			for(int y = 0; y < H_RES; y++)
			{

				if (y >= drawStart && y <= drawEnd)
				{
					int texY = (int) texPos & (texHeight - 1);
					texPos += step;
					uint32_t color = get_pixel(img, texX,texY);
					put_pixel(&set->rend->main_img, x, y, shadows(color,
							wall_distance));
				}
				else
					put_pixel(&set->rend->main_img, x, y, get_pixel
					(&set->rend->back_img, x, y));
			}
	}
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, (set->rend->main_img.img), 0, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->rend->fire
	.img[set->rend->fire.i].img, -200, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->rend->minimap
	.img, W_RES - set->game->map_width * 8, H_RES -
	set->game->map_height
	* 8);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->game->hero.img,
		W_RES - 8 * set->game->map_width + (int)(set->game->hero_pos.x * 8)
		- 1,
		H_RES - 8 * set->game->map_height + (int)(set->game->hero_pos.y *
												  8) -
		1);
	set->rend->fire.i++;
	if (set->rend->fire.i == 20)
		set->rend->fire.i = 0;
	i = 0;
	while (i < 5000000)
		i++;

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
	movement_processor(set);
	render_image(set);
//	if (set->game->win)
//		leave_game(set);
	return (1);
}
