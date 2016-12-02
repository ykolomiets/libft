/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:29 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:36:33 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*temp;

	if (!(s1 && s2))
		return (NULL);
	res = (char*)malloc(sizeof(char) * (ft_strlen(s1) +
				ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	temp = res;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (res);
}
