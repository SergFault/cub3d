/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:34 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:34 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	if (!dst || !src)
		return (0);
	counter = ft_strlen(src);
	if (!size)
		return (counter);
	while (((size--) > 1) && (*src))
		*(dst++) = *(src++);
	*dst = '\0';
	return (counter);
}
