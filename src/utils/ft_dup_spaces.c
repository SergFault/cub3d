/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:31:04 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/17 13:54:37 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_dup_spaces(size_t size)
{
	char	*dup;
	int i;

	i = 0;
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!(dup))
		return (0);
	while (i < size)
		dup[i++] = ' ';
	dup[i] = '\0';
	return (dup);
}