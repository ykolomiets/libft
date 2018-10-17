/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:48:42 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:54:11 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

t_boolean	bi_is_zero(t_big_int *big_int)
{
	return (big_int->length == 0);
}

void		bi_set_u32(t_big_int *big_int, uint32_t val)
{
	if (val != 0)
	{
		big_int->blocks[0] = val;
		big_int->length = 1;
	}
	else
	{
		big_int->length = 0;
	}
}

uint32_t	bi_get_u32(t_big_int *big_int)
{
	return (big_int->length == 0 ? 0 : big_int->blocks[0]);
}

void		bi_set_u64(t_big_int *big_int, uint64_t val)
{
	if (val > 0xFFFFFFFF)
	{
		big_int->blocks[0] = val & 0xFFFFFFFF;
		val >>= 32;
		big_int->blocks[1] = val & 0xFFFFFFFF;
		big_int->length = 2;
	}
	else if (val != 0)
	{
		big_int->blocks[0] = val & 0xFFFFFFFF;
		big_int->length = 1;
	}
	else
	{
		big_int->length = 0;
	}
}

int			bi_compare(t_big_int *left, t_big_int *right)
{
	uint32_t	len_diff;
	int			i;

	len_diff = left->length - right->length;
	if (len_diff)
		return (len_diff);
	i = left->length;
	while (--i >= 0)
	{
		if (left->blocks[i] == right->blocks[i])
			continue;
		else if (left->blocks[i] > right->blocks[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}
