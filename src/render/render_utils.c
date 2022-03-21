/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:51 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 20:16:00 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_tex_mapping(t_eng *e)
{
	e->draw_start = -(e->line_height) / 2 + H_RES / 2;
	if (e->draw_start < 0)
		e->draw_start = 0;
	e->draw_end = (e->line_height) / 2 + H_RES / 2;
	if (e->draw_end >= H_RES)
		e->draw_end = H_RES - 1;
	if (e->chosen_text == e->texture[X])
		e->wall_x = -(e->pos[Y] + e->wall_dist * e->ray_dir_y);
	else
		e->wall_x = (e->pos[X] + e->wall_dist * e->ray_dir_x);
	e->wall_x -= floor((e->wall_x));
	e->tex[X] = (int)(e->wall_x * (double) TEX_W);
	e->tex_step = 1.0 * TEX_H / e->line_height;
	e->tex_pos = (e->draw_start - (double) H_RES / 2
			+ (double) e->line_height / 2) * e->tex_step;
}

t_img	*choose_image(int side, t_dataset *set)
{
	if (side == NORTH_SIDE)
		return (&set->rend->north);
	else if (side == WEST_SIDE)
		return (&set->rend->west);
	else if (side == EAST_SIDE)
		return (&set->rend->east);
	else
		return (&set->rend->south);
}

static void	put_images_to_window(t_dataset *set)
{
	mlx_put_image_to_window(set->rend->mlx, set->rend->win,
		(set->rend->main_img.img), 0, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->rend->fire
		.img[set->rend->fire.i].img, -200, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win,
		set->rend->minimap.img, W_RES - set->game->map_w * 8,
		H_RES - set->game->map_h * 8);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->game->hero.img,
		W_RES - 8 * set->game->map_w + (int)(set->game->hero_pos.x * 8) - 1,
		H_RES - 8 * set->game->map_h + (int)(set->game->hero_pos.y * 8) - 1);
	set->rend->fire.i++;
	if (set->rend->fire.i == 20)
		set->rend->fire.i = 0;
}

static void	put_vertical_pixels(const t_dataset *set, t_eng *e, int x)
{
	int	y;

	y = 0;
	while (y < H_RES)
	{
		if (y >= (*e).draw_start && y <= (*e).draw_end)
		{
			(*e).tex[Y] = (int)(*e).tex_pos & (TEX_H - 1);
			(*e).tex_pos += (*e).tex_step;
			put_pixel(&set->rend->main_img, x, y, shadows(get_pixel(
						(*e).image, (*e).tex[X], (*e).tex[Y]), (*e).wall_dist));
		}
		else
			put_pixel(&set->rend->main_img, x, y, get_pixel
				(&set->rend->back_img, x, y));
		y++;
	}
}

void	render_image(t_dataset *set)
{
	t_eng	e;
	int		x;

	e.pos[X] = set->game->hero_pos.x;
	e.pos[Y] = set->game->hero_pos.y;
	e.dir[X] = set->game->hero_pos.dir_x;
	e.dir[Y] = set->game->hero_pos.dir_y;
	e.plane[X] = set->game->hero_pos.cam_plane_x;
	e.plane[Y] = set->game->hero_pos.cam_plane_y;
	x = 0;
	while (x < W_RES)
	{
		calculate_ray(&e, x);
		calculate_ray_step(&e);
		calculate_crossover(&e, set);
		calculate_normale_ray(&e);
		e.line_height = (int)(H_RES / e.wall_dist);
		calculate_tex_mapping(&e);
		e.image = choose_image(e.chosen_text, set);
		put_vertical_pixels(set, &e, x);
		x++;
	}
	put_images_to_window(set);
}
