/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:17:58 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 22:26:50 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*(unsigned char*)s1 == *(unsigned char *)s2 && n--)
	{
		if (n == 0)
			return (0);
		s1 = (unsigned char*)s1 + 1;
		s2 = (unsigned char*)s2 + 1;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
