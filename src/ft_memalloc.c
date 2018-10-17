/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:17:51 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:33:46 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*res;

	res = (char*)malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	while (size--)
		res[size] = 0;
	return (res);
}
