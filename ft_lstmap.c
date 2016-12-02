/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 18:49:18 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 18:49:20 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	del(void *content, size_t size)
{
	if (!content || !size)
		return ;
	free(content);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	**step;

	if (!lst || !f)
		return (NULL);
	new_list = (*f)(lst);
	if (!new_list)
		return (NULL);
	step = &new_list->next;
	lst = lst->next;
	while (lst)
	{
		*step = (*f)(lst);
		if (*step == NULL)
		{
			ft_lstdel(&new_list, del);
			return (NULL);
		}
		step = &(*step)->next;
		lst = lst->next;
	}
	return (new_list);
}
