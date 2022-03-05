/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:32 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:32 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dup))
		return (0);
	ft_strlcpy(dup, s, (len + 1));
	return (dup);
}
