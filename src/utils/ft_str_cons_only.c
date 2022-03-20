/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cons_only.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:22 by sergey            #+#    #+#             */
/*   Updated: 2022/03/20 19:45:12 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_str_cons_only_chars(char *str, char *str_ch)
{
	int	i;

	while (*str)
	{
		i = 0;
		while (str_ch[i])
		{
			if (str_ch[i] == *str || ft_is_space(*str))
				break ;
			if (str_ch[i] == '\0')
				return (0);
			i++;
		}
		str++;
	}
	return (1);
}

int	ft_str_cons_only(char *str, char ch)
{
	while (*str)
	{
		if (*str == ch)
			return (1);
		str++;
	}
	return (0);
}
