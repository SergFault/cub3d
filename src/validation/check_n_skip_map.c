/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_skip_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:59:33 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 13:59:56 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	max_width(t_list *lines)
{
	int	width;

	width = 0;
	while (lines)
	{
		if (width < ft_strlen(lines->content))
			width = (int)ft_strlen(lines->content);
		lines = lines->next;
	}
	return (width);
}

void	write_end(t_list *lines, int width)
{
	char	*end;
	char	*temp;

	end = NULL;
	while (lines)
	{
		if (ft_strlen(lines->content) < width)
		{
			end = ft_dup_spaces(width - ft_strlen(lines->content));
			temp = lines->content;
			lines->content = ft_strjoin(lines->content, end);
			free(temp);
			free(end);
		}
		lines = lines->next;
	}
}

int	check_n_skip_map(t_list **line_lst, t_dataset *set)
{
	t_list	*iter;

	iter = *line_lst;
	while (iter != 0
		&& ft_str_cons_only_chars((char *) iter->content, VALID_CHARS))
		iter = iter->next;
	if (iter != NULL)
		return (0);
	iter = *line_lst;
	write_end(iter, max_width(iter));
	set->game->map = str_lines_to_arr(iter, set->game);
	if (!set->game->map)
		return (0);
	return (1);
}
