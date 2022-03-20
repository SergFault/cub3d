/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:43:42 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 21:51:29 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	leave_game(t_dataset *set)
{
	free_data(set);
	free_map(set->game->map);
	mlx_destroy_image(set->rend->mlx, set->rend->main_img.img);
	if (set->rend->north.img)
		mlx_destroy_image(set->rend->mlx, set->rend->north.img);
	if (set->rend->south.img)
		mlx_destroy_image(set->rend->mlx, set->rend->south.img);
	if (set->rend->west.img)
		mlx_destroy_image(set->rend->mlx, set->rend->west.img);
	if (set->rend->east.img)
		mlx_destroy_image(set->rend->mlx, set->rend->east.img);
	mlx_destroy_window(set->rend->mlx, set->rend->win);
	exit(0);
}
