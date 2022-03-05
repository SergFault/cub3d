/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:28:20 by sergey            #+#    #+#             */
/*   Updated: 2021/09/29 17:28:20 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		un = -1 * n;
	}
	else
		un = n;
	if (un > 9)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd((char)(un % 10 + '0'), fd);
}
