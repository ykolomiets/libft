/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:59 by ykolomie          #+#    #+#             */
/*   Updated: 2016/11/30 22:20:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		needle_len;
	int		i;
	char	*result;

	needle_len = 0;
	while (needle[needle_len])
		needle_len++;
	if (!needle_len)
		return ((char*)haystack);
	while (*(haystack))
	{
		i = 0;
		result = (char*)haystack;
		while (i < needle_len)
			if (result[i] != needle[i])
				break ;
			else
				i++;
		if (i == needle_len)
			return (result);
		haystack++;
	}
	return (0);
}
