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

static int is_color(t_list *line)
{
	return (ft_strncmp((char *) line->content, "F ", 2) == 0
			|| ft_strncmp((char *) line->content, "C ", 2) == 0);
}

static int is_tex_path(t_list *line)
{
	return (ft_strncmp((char *) line->content, "NO ", 3) == 0
			|| ft_strncmp((char *) line->content, "SO ", 3) == 0
			|| ft_strncmp((char *) line->content, "WE ", 3) == 0
			|| ft_strncmp((char *) line->content, "EA ", 3) == 0);
}

static int is_empt(t_list *line)
{
	return (((char *) line->content)[0] == '\0') ;
}

static void skip_nl(t_list **line)
{
	while (*line && ((char *)(*line)->content)[0] == '\0')
		*line = (*line)->next;
}

int validate_lines(t_list *line_lst, t_dataset *set)
{
	while (line_lst && (is_color(line_lst) || is_tex_path(line_lst) || is_empt((line_lst))))
	{
		skip_nl(&line_lst);
		if (is_tex_path(line_lst))
			if (!check_n_skip_textures(&line_lst, set))
				return (0);
		if (is_color(line_lst))
			if (!check_n_skip_colors(&line_lst, set))
				return (0);
	}
	if (!have_all_meta_data(set))
		return (0);
	if (line_lst && !check_n_skip_map(&line_lst, set))
	{
		free_map(set->game->map);
		free_textures_paths(set);
		return (0);
	}
	return (1);
}
