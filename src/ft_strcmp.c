/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:09 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/02 19:25:49 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*((unsigned char*)s1++) == *((unsigned char*)s2++))
		if (*((unsigned char*)s1) == '\0' && *((unsigned char*)s2) == '\0')
			return (0);
	return ((int)(*((unsigned char*)--s1) - *((unsigned char*)--s2)));
}
