/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:31 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:46:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	old_size;

	dest_size = 0;
	while (dst[dest_size] != '\0' && dest_size < size)
		dest_size++;
	src_size = 0;
	src_size = ft_strlen(src);
	old_size = dest_size;
	while (src[dest_size - old_size] != '\0' && dest_size < size - 1)
	{
		dst[dest_size] = src[dest_size - old_size];
		dest_size++;
	}
	if (old_size < size)
		dst[dest_size] = '\0';
	return (old_size + src_size);
}
