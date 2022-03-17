/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sergey <mrserjy@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:29:31 by Sergey            #+#    #+#             */
/*   Updated: 2022/03/15 18:53:07 by Sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_rank(unsigned int num)
{
	unsigned int	rank;

	if (!(num))
		return (1);
	rank = 0;
	while (num > 0)
	{
		rank++;
		num /= 10;
	}
	return (rank);
}

static int	ft_getsign(int num)
{
	if (num < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int				rank;
	int				sign;
	unsigned int	num;
	char			*ret;

	sign = ft_getsign(n);
	num = n;
	if (sign)
		num = -n;
	rank = ft_rank(num) + sign;
	ret = (char *)malloc(sizeof(char) * (rank + 1));
	//todo error handling
	ret[rank] = '\0';
	while (num > 9)
	{
		ret[rank-- - 1] = (num % 10) + ('0' + 0);
		num /= 10;
	}
	ret[rank-- - 1] = (num) + ('0' + 0);
	num = 0;
	if (sign)
		ret[rank - 1] = '-';
	return (ret);
}
