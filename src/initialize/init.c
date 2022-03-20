/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:40 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 19:20:09 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_img_null(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_data(t_dataset *set)
{
	int	i;

	set->ce_rgb[0] = -1;
	set->fl_rgb[0] = -1;
	set->rend->mlx = NULL;
	set->rend->win = NULL;
	set->path_north = NULL;
	set->path_west = NULL;
	set->path_south = NULL;
	set->path_east = NULL;
	set_img_null(&set->rend->east);
	set_img_null(&set->rend->west);
	set_img_null(&set->rend->north);
	set_img_null(&set->rend->south);
	set_img_null(&set->rend->main_img);
	i = 0;
	while (i < 256)
	{
		set->k[i] = tan((double)(i * ((double)H_RES / 256)) / 650);
		i++;
	}
	set->rend->i = 0;
	set->game->map_width = 0;
	set->game->map_height = 0;
	set->game->map = NULL;
}

static int	init_model(void *mlx, t_img img[10], char *path)
{
	img->img = mlx_png_file_to_image(mlx, path, &(img->width), &(img->height));
	if (!img->img)
		return ((int)ft_error_null(TEXTURES_INIT_ERROR));
	img->address = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	return (1);
}

int	init_fire(void *mlx, t_fire *fire)
{
	char	*path;
	int		res;

	path = ft_strdup("textures/fire/0000.png");
	if (!path)
		return (0);
	fire->i = 0;
	res = 0;
	while (fire->i < 20)
	{
		fire->img[fire->i].img = mlx_png_file_to_image(mlx, path,
				&(fire->img[fire->i].width), &(fire->img[fire->i].height));
		if (fire->img[fire->i].img)
			res++;
		fire->i++;
		if (fire->i == 10)
		{
			path[16]++;
			path[17] = '0';
		}
		else
			path[17]++;
	}
	free(path);
	return (fire->i == res);
}

int	rend_init(t_dataset *set)
{
	set->rend->mlx = mlx_init();
	set->rend->win = mlx_new_window(set->rend->mlx, W_RES, H_RES, "cub3d");
	set->rend->main_img.img = mlx_new_image(set->rend->mlx, W_RES, H_RES);
	set->rend->main_img.address = mlx_get_data_addr(set->rend->main_img.img,
			&set->rend->main_img.bpp, &set->rend->main_img.line_length,
			&set->rend->main_img.endian);
	set->rend->back_img.img = mlx_new_image(set->rend->mlx, W_RES, H_RES);
	set->rend->back_img.address = mlx_get_data_addr(set->rend->back_img.img,
			&set->rend->back_img.bpp, &set->rend->back_img.line_length,
			&set->rend->back_img.endian);
	set->rend->minimap.img = mlx_new_image(set->rend->mlx,
			set->game->map_width * 8, set->game->map_height * 8);
	set->rend->minimap.address = mlx_get_data_addr(set->rend->minimap.img,
			&set->rend->minimap.bpp, &set->rend->minimap.line_length,
			&set->rend->minimap.endian);
	set->game->hero.img = mlx_new_image(set->rend->mlx, 3, 3);
	set->game->hero.address = mlx_get_data_addr(set->game->hero.img,
			&set->game->hero.bpp, &set->game->hero.line_length,
			&set->game->hero.endian);
	return (init_model(set->rend->mlx, &set->rend->west, set->path_west)
		&& init_model(set->rend->mlx, &set->rend->east, set->path_east)
		&& init_model(set->rend->mlx, &set->rend->north, set->path_north)
		&& init_model(set->rend->mlx, &set->rend->south, set->path_south)
		&& init_fire(set->rend->mlx, &set->rend->fire));
}
