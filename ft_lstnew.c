/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:49:20 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/05 10:38:32 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	res = (t_list*)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	if (!content)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		res->content = malloc(content_size);
		if (!res->content)
		{
			free(res);
			return (NULL);
		}
		ft_memcpy(res->content, content, content_size);
		if (!res->content)
			return (NULL);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
