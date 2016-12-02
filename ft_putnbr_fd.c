/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:18:50 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:47:56 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_put(int n, int fd)
{
	char	c;

	if (!n)
		return ;
	ft_put(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (fd < 1)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		ft_put(n, fd);
	}
}
