/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_skip_colors_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstepani <rstepani@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:33:00 by rstepani          #+#    #+#             */
/*   Updated: 2022/03/22 13:23:32 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	thee_digits_check_skip(char **str)
{
	int	i;

	i = 0;
	while (*str && ft_is_digit(**str) && i < 3)
	{
		(*str)++;
		i++;
	}
	if (i > 0)
		return (1);
	return (0);
}

static int	comma_check_skip(char **str)
{
	if (*str && **str == ',')
	{
		(*str)++;
		return (1);
	}
	return (0);
}

static int	space_check_skip(char **str)
{
	while (*str && **str == ' ')
	{
		(*str)++;
	}
	return (1);
}

int	is_valid_color_pattern(char *str)
{
	if (space_check_skip(&str)
		&& thee_digits_check_skip(&str)
		&& comma_check_skip(&str)
		&& thee_digits_check_skip(&str)
		&& comma_check_skip(&str)
		&& thee_digits_check_skip(&str)
		&& *str == '\0')
		return (1);
	return (0);
}
