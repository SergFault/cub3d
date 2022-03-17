/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 20:48:56 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 20:25:05 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int validate_lines(t_list *line_lst, t_dataset *set)
{
	if (!check_n_skip_textures(&line_lst, set))
	{
		free_textures_paths(set);
		return (0);
	}
	if (!check_n_skip_colors(&line_lst, set))
	{
		free_textures_paths(set);
		return (0);
	}
	if (!check_n_skip_map(&line_lst, set))
	{
		free_map(set->game->map);
		free_textures_paths(set);
		return (0);
	}
	return (1);
}
