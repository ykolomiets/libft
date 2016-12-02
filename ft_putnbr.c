/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:18:49 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:45:30 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	ft_print(int n)
{
	if (!n)
		return ;
	ft_print(n / 10);
	ft_putchar(n % 10 + 48);
}

void		ft_putnbr(int n)
{
	if (n == 0)
		ft_putchar('0');
	else if (n == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		ft_print(n);
	}
}
