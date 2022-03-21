/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstepani <rstepani@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:33:00 by rstepani          #+#    #+#             */
/*   Updated: 2022/03/15 19:21:42 by rstepani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray(t_eng *e, int num)
{
	e->pos_int[X] = (int) e->pos[X];
	e->pos_int[Y] = (int) e->pos[Y];
	e->camera_x = 2 * num / (double) W_RES - 1;
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

void	calculate_ray_step(t_eng *e)
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

void	calculate_normale_ray(t_eng *e)
{
	if (e->chosen_text == e->texture[X])
		e->wall_dist = (e->side_dist[X] - e->dist_d[X]);
	else
		e->wall_dist = (e->side_dist[Y] - e->dist_d[Y]);
}
