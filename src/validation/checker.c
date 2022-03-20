/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:08 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 18:29:25 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *argv)
{
	if (ft_strlen(argv) < 5)
		return (0);
	while (argv[4])
	{
		if (argv[1] == '.' && argv[2] == 'c' && argv[3] == 'u' && argv[4]
			=='b' && argv[5] == '\0')
			return (1);
		argv++;
	}
	return (0);
}

static int	check_chars(char **map, int map_width, int map_height)
{
	char	*valid;
	int		i;
	int		j;

	i = 0;
	valid = VALID_CHARS;
	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (!ft_str_cons_only(valid, map[i][j]))
				return (0);
		}
	}
	return (1);
}

static int	have_bad_neighbor(char **map, int y, int x, t_game *game)
{
	if (y <= 0 || x <= 0
		|| y >= game->map_height - 1 || x >= game->map_width - 1)
		return (1);
	if (map[y - 1][x] == SPACE_CH || map[y + 1][x] == SPACE_CH
		|| map[y][x - 1] == SPACE_CH || map[y][x + 1] == SPACE_CH)
		return (1);
	return (0);
}

static int	check_walls(char **map, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map [i][j])
		{
			if (map[i][j] != WALL_CH && map[i][j] != SPACE_CH)
				if (have_bad_neighbor(map, i, j, game))
					return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	validate_map(char **map, t_game *game)
{
	if (!(check_map_content(map))
		|| !(check_walls(map, game))
		|| check_chars(map, game->map_width, game->map_height))
		return (0);
	return (1);
}
