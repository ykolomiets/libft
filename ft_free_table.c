/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:34:09 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/05 09:47:54 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_table(char ***table, int size)
{
	int	i;

	i = 0;
	while (i < size && (*table)[i])
		free((*table)[i++]);
	free(*table);
	*table = NULL;
}
