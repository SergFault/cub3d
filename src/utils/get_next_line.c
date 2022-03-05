/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:37 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:37 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_cached_nl(char **cache, char **line)
{
	int		counter;

	if (!(*cache))
		return (0);
	counter = 0;
	while ((*cache)[counter] != '\n')
		if ((*cache)[counter++] == '\0')
			return (0);
	(*cache)[counter] = '\0';
	if ((ft_sj_ff_dt(*line, *cache, line)) == -1)
	{
		free(*line);
		*line = NULL;
	}
	if (ft_strdup_free((*cache + counter + 1), cache) == -1)
	{
		if (*line)
			free(*line);
		*line = NULL;
	}
	return (1);
}

static int	process_cache(char **cache, char **line)
{
	if (!(*cache))
		return (0);
	if ((ft_strdup_free(*cache, line)) == -1)
		return (-1);
	if ((ft_strdup_free("", cache)) == -1)
		return (-1);
	return (1);
}

static	int	free_ret(int ret, char **buffer, char **cache)
{
	if ((ret == -1 || ret == 0) && (cache && *cache))
	{
		free(*cache);
		*cache = NULL;
	}
	if (buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (ret);
}

static int	read_fd(char **line, char *buffer[], char **cache, int fd)
{
	int	do_read;
	int	read_counter;

	do_read = 1;
	read_counter = 1;
	while (do_read && read_counter)
	{
		read_counter = read(fd, buffer[0], BUFFER_SIZE);
		buffer[0][read_counter] = '\0';
		buffer[1] = ft_strchr(buffer[0], '\n');
		if (buffer[1])
		{
			do_read = 0;
			*buffer[1] = '\0';
			if (!(ft_sj_ff_dt(*cache, buffer[1] + 1, cache)))
				return (-1);
		}
		if (!(ft_sj_ff_dt(*line, buffer[0], line)))
			return (-1);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer[2];
	static char	*cache;

	buffer[1] = NULL;
	buffer[0] = NULL;
	if ((read(fd, NULL, 0) < 0) || !line || fd < 0
		|| (ft_sj_ff_dt(NULL, "", line) == -1))
		return (free_ret(-1, NULL, &cache));
	if (check_cached_nl(&cache, line))
	{
		if (*line)
			return (1);
		else if (!(*line))
			return (free_ret(-1, NULL, &cache));
	}
	if (process_cache(&cache, line) == -1)
		return (free_ret(-1, NULL, &cache));
	buffer[0] = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!(buffer[0]) || read_fd(line, buffer, &cache, fd) == -1)
		return (free_ret(-1, &buffer[0], &cache));
	if (ft_strlen(cache) || buffer[1])
		return (free_ret(1, &buffer[0], NULL));
	return (free_ret(0, &buffer[0], &cache));
}
