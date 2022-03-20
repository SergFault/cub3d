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

void	init_engine(t_eng *e, t_dataset *set)
{
	e->pos[X] = set->game->hero_pos.x;
	e->pos[Y] = set->game->hero_pos.y;
	e->dir[X] = set->game->hero_pos.dir_x;
	e->dir[Y] = set->game->hero_pos.dir_y;
	e->plane[X] = set->game->hero_pos.cam_plane_x;
	e->plane[Y] = set->game->hero_pos.cam_plane_y;
}

void	calculate_ray(t_eng *e, t_dataset *set, int num)
{
	e->camera_x = 2 * num / (double) W_RES - 1; //x-coordinate in camera space
	e->ray_dir_x = e->dir[X] + e->plane[X] * e->camera_x;
	e->ray_dir_y = e->dir[Y] + e->plane[Y] * e->camera_x;
	if (e->ray_dir_x == 0)
		e->dist_d[X] = 1e30;
	else
		e->dist_d[X] = ft_abs(1 / e->ray_dir_x);
	if (e->ray_dir_y == 0)
		e->dist_d[Y] = 1e30;
	else
		e->dist_d[Y] = ft_abs(1 / e->ray_dir_y);
}

void	calculate_texture_side(t_eng *e)
{
	if (e->ray_dir_y < 0)
		e->texture[Y] = NORTH_SIDE;
	else
		e->texture[Y] = SOUTH_SIDE;
	if (e->ray_dir_x > 0)
		e->texture[X] = EAST_SIDE;
	else
		e->texture[X] = WEST_SIDE;
}

void	calculate_ray_step(t_eng *e, t_dataset *set)
{
	if (e->ray_dir_x < 0)
	{
		e->step[X] = -1;
		e->side_dist[X] = (e->pos[X] - e->pos_int[X]) * e->dist_d[X];
	}
	else
	{
		e->step[X] = 1;
		e->side_dist[X] = (e->pos_int[X] + 1.0 - e->pos[X]) * e->dist_d[X];
	}
	if (e->ray_dir_y < 0)
	{
		e->step[Y] = -1;
		e->side_dist[Y] = (e->pos[Y] - e->pos_int[Y]) * e->dist_d[Y];
	}
	else
	{
		e->step[Y] = 1;
		e->side_dist[Y] = (e->pos_int[Y] + 1.0 - e->pos[Y]) * e->dist_d[Y];
	}
}

void	calculate_crossover(t_eng *e, t_dataset *set)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		calculate_texture_side(e);
		if (e->side_dist[X] < e->side_dist[Y])
		{
			e->side_dist[X] += e->dist_d[X];
			e->pos_int[X] += e->step[X];
			e->chosen_text = e->texture[X];
		}
		else
		{
			e->side_dist[Y] += e->dist_d[Y];
			e->pos_int[Y] += e->step[Y];
			e->chosen_text = e->texture[Y];
		}
		if ((set->game->map)[e->pos_int[Y]][e->pos_int[X]] == '1')
			hit = 1;
	}
}

void	calculate_normale_ray(t_eng *e, t_dataset *set)
{
	if (e->chosen_text == e->texture[X])
		e->wall_distance = (e->side_dist[X] - e->dist_d[X]);
	else
		e->wall_distance = (e->side_dist[Y] - e->dist_d[Y]);
}

void	calculate_tex_mapping(t_eng *e)
{
	e->draw_start = -(e->line_height) / 2 + H_RES / 2;
	if (e->draw_start < 0)
		e->draw_start = 0;
	e->draw_end = (e->line_height) / 2 + H_RES / 2;
	if (e->draw_end >= H_RES)
		e->draw_end = H_RES - 1;
	if (e->chosen_text == e->texture[X])
		e->wall_x = -(e->pos[Y] + e->wall_distance * e->ray_dir_y);
	else
		e->wall_x = (e->pos[X] + e->wall_distance * e->ray_dir_x);
	e->wall_x -= floor((e->wall_x));
	e->tex[X] = (int)(e->wall_x * (double) texWidth);
	e->tex_step = 1.0 * texHeight / e->line_height;
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

static int	render_image(t_dataset *set)
{
	t_eng	e;

	init_engine(&e, set);
	for (int x = 0; x < W_RES; x++)
	{
		e.pos_int[X] = (int) e.pos[X];
		e.pos_int[Y] = (int) e.pos[Y];
		calculate_ray(&e, set, x);
		calculate_ray_step(&e, set);
		calculate_crossover(&e, set);
		calculate_normale_ray(&e, set);
		e.line_height = (int) (H_RES / e.wall_distance);
		calculate_tex_mapping(&e);
		e.image = choose_image(e.chosen_text, set);
		for (int y = 0; y < H_RES; y++)
		{

			if (y >= e.draw_start && y <= e.draw_end)
			{
				e.tex[Y] = (int) e.tex_pos & (texHeight - 1);
				e.tex_pos += e.tex_step;
				uint32_t color = get_pixel(e.image, e.tex[X], e.tex[Y]);
				put_pixel(&set->rend->main_img, x, y, shadows(color, e.wall_distance));
			} else
				put_pixel(&set->rend->main_img, x, y, get_pixel
					(&set->rend->back_img, x, y));
		}
	}
	mlx_put_image_to_window(set->rend->mlx, set->rend->win,
		(set->rend->main_img.img), 0, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->rend->fire
		.img[set->rend->fire.i].img, -200, 0);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->rend->minimap
		.img, W_RES - set->game->map_width * 8, H_RES -
													   set->game->map_height
													   * 8);
	mlx_put_image_to_window(set->rend->mlx, set->rend->win, set->game->hero.img,
		W_RES - 8 * set->game->map_width +
		(int) (set->game->hero_pos.x * 8)
		- 1,
		H_RES - 8 * set->game->map_height +
		(int) (set->game->hero_pos.y *
			   8) -
		1);
	set->rend->fire.i++;
	if (set->rend->fire.i == 20)
		set->rend->fire.i = 0;
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
