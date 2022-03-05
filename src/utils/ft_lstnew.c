/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:14 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:14 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newl;

	newl = malloc(sizeof(t_list));
	if (!(newl))
		return (0);
	newl->content = content;
	newl->next = 0;
	newl->prev = 0;
	return (newl);
}
