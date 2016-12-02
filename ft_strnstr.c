/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:51 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/02 19:45:04 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if ((needle_len = ft_strlen(needle)) == 0)
		return ((char*)haystack);
	i = 0;
	while (*haystack && len - i >= needle_len)
	{
		if ((haystack[0] == needle[0]) &&
				(ft_strncmp(haystack, needle, needle_len) == 0))
			return ((char*)haystack);
		haystack++;
		i++;
	}
	return (0);
}
