/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:17:48 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:46:48 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_res_size(int n)
{
	int res;

	res = 0;
	if (n <= 0)
		res++;
	while (n)
	{
		res++;
		n /= 10;
	}
	return (res);
}

static int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

static void	ft_fill_res(char *str, int n, int size)
{
	while (size)
	{
		str[size - 1] = ft_abs(n % 10) + '0';
		n /= 10;
		size--;
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		res_size;

	res_size = ft_res_size(n);
	res = (char*)malloc(sizeof(char) * (res_size + 1));
	if (!res)
		return (NULL);
	res[res_size] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		ft_fill_res(res + 1, n, res_size - 1);
	}
	else
		ft_fill_res(res, n, res_size);
	return (res);
}
