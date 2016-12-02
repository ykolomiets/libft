/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:07:37 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:52:17 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	len;

	if (!(s && f))
		return (NULL);
	len = ft_strlen(s);
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len--)
		res[len] = (*f)((unsigned int)len, s[len]);
	return (res);
}
