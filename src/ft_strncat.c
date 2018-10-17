/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:41 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 19:39:51 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	*res;

	res = dest;
	while (*dest)
		dest++;
	i = 0;
	while (src[i] && i < n)
	{
		*dest = src[i++];
		dest++;
	}
	*dest = '\0';
	return (res);
}
