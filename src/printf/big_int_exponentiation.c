/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_exponentiation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:20:20 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:20:22 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

static void	swap_bi_pointers(t_big_int **a, t_big_int **b)
{
	t_big_int	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void		bi_pow10(t_big_int *result, uint32_t exp)
{
	t_big_int	temp1;
	t_big_int	temp2;
	t_big_int	*cur_temp;
	t_big_int	*next_temp;
	uint32_t	table_idx;

	cur_temp = &temp1;
	next_temp = &temp2;
	bi_set_u32(cur_temp, get_pow10_uint32(exp & 0x7));
	exp >>= 3;
	table_idx = 0;
	while (exp)
	{
		if (exp & 1)
		{
			bi_mult_bi_by_bi(next_temp, cur_temp, get_pow10_big_int(table_idx));
			swap_bi_pointers(&next_temp, &cur_temp);
		}
		table_idx++;
		exp >>= 1;
	}
	*result = *cur_temp;
}

void		bi_mult_by_pow10(t_big_int *result, t_big_int *in, uint32_t exp)
{
	t_big_int	temp1;
	t_big_int	temp2;
	t_big_int	*cur_temp;
	t_big_int	*next_temp;
	uint32_t	table_idx;

	cur_temp = &temp1;
	next_temp = &temp2;
	if (exp & 0x7)
		bi_mult_bi_by_uint32(cur_temp, in, get_pow10_uint32(exp & 0x7));
	else
		*cur_temp = *in;
	exp >>= 3;
	table_idx = 0;
	while (exp)
	{
		if (exp & 1)
		{
			bi_mult_bi_by_bi(next_temp, cur_temp, get_pow10_big_int(table_idx));
			swap_bi_pointers(&next_temp, &cur_temp);
		}
		table_idx++;
		exp >>= 1;
	}
	*result = *cur_temp;
}

void		bi_pow2(t_big_int *result, uint32_t exp)
{
	uint32_t	block_idx;
	uint32_t	bit_idx;
	uint32_t	i;

	block_idx = exp / 32;
	i = 0;
	while (i <= block_idx)
	{
		result->blocks[i] = 0;
		i++;
	}
	result->length = block_idx + 1;
	bit_idx = exp % 32;
	result->blocks[block_idx] |= (1 << bit_idx);
}
