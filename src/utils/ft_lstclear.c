/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:09 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:09 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*iter;
	t_list	*todel;

	if (!lst || !*lst)
		return ;
	iter = *lst;
	while (iter)
	{
		todel = iter;
		iter = iter->next;
		if (del)
			del(todel->content);
		free(todel);
	}
	*lst = 0;
}
