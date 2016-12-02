/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:43 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/02 19:36:05 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (*((unsigned char*)s1++) == *((unsigned char*)s2++) && i++ < n)
		if ((*((unsigned char*)s1) == '\0' && *((unsigned char*)s2) == '\0') || i == n)
			return (0);
	return ((int)(*((unsigned char*)--s1) - *((unsigned char*)--s2)));
}
