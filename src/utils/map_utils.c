/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:27:40 by sergey            #+#    #+#             */
/*   Updated: 2022/03/05 16:58:28 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	gnl_map(int fd, t_list **lines)
{
	int		read_flag;
	char	*line;

	line = NULL;
	read_flag = 1;
	while (read_flag)
	{
		read_flag = get_next_line(fd, &line);
		if (read_flag == -1)
		{
			ft_lstclear(lines, ft_lst_del_str);
			ft_putstr_fd(BAD_FILE, 1);
			close(fd);
			return (-1);
		}
		ft_lstadd_back(lines, ft_lstnew(line));
	}
	close(fd);
	return (1);
}

static void	count_lines_and_chars(t_list *lines, t_game *game)
{
	int	tmp;

	game->map_width = 0;
	game->map_height = 0;
	while (lines)
	{
		game->map_height += 1;
		tmp = ft_strlen((char *)lines->content);
		if (tmp > game->map_width)
			game->map_width = tmp;
		lines = lines->next;
	}
}

static char	**str_lines_to_arr(t_list *lines, t_game *game)
{
	char	**str_arr;
	int		tmp;
	t_list	*start;

	start = lines;
	count_lines_and_chars(lines, game);
	str_arr = (char **) malloc((sizeof (char *)) * game->map_height);
	if (str_arr == NULL)
		ft_error_null(MEM_ERR);
	tmp = 0;
	lines = start;
	while (lines)
	{
		str_arr[tmp] = ft_strdup(lines->content);
		if (!(str_arr[tmp++]))
		{
			free_str_array(str_arr, --tmp);
			free(str_arr);
			return (ft_error_null(MEM_ERR));
		}
		lines = lines->next;
	}
	return (str_arr);
}

static t_list	*lines_list(t_list *lines, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if ((read(fd, NULL, 0) < 0) || fd < 0)
	{
		ft_putstr_fd(BAD_FD, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	fd = gnl_map(fd, &lines);
	if (fd == -1)
		exit(EXIT_FAILURE);
	return (lines);
}

int	map_init(t_game *game, char **argv)
{
	t_list	*lines;

	lines = NULL;
	if (!(check_extension(argv[1])))
	{
		ft_putstr_fd(MAP_EXT_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	lines = lines_list(lines, argv[1]);
	if (!(validate_map(lines)))
	{
		ft_lstclear(&lines, ft_lst_del_str);
		ft_putstr_fd(MAP_VALID_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	game->map = str_lines_to_arr(lines, game);
	ft_lstclear(&lines, ft_lst_del_str);
	if (!(game->map))
	{
		ft_putstr_fd(MAP_VALID_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (1);
}
