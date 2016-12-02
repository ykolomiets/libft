/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:17:54 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 19:39:35 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;

	t_dest = (unsigned char*)dest;
	t_src = (unsigned char*)src;
	if (n)
	{
		while (n--)
			if ((*t_dest++ = *t_src++) == (unsigned char)c)
				return (t_dest);
	}
	return (NULL);
}
