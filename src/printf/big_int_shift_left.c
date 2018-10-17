/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_shift_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:36:17 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:36:19 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

static void	shift_aligned(t_big_int *result, uint32_t shift_blocks)
{
	uint32_t	*in_cur;
	uint32_t	*out_cur;
	uint32_t	i;

	in_cur = result->blocks + result->length;
	out_cur = in_cur + shift_blocks;
	while (in_cur >= result->blocks)
	{
		*out_cur = *in_cur;
		in_cur--;
		out_cur--;
	}
	i = 0;
	while (i < shift_blocks)
		result->blocks[i++] = 0;
	result->length += shift_blocks;
}

static void	zero_low_blocks(t_big_int *result, uint32_t blocks)
{
	uint32_t	i;

	i = 0;
	while (i < blocks)
		result->blocks[i++] = 0;
}

static void	shift_not_aligned
(
		t_big_int *result,
		uint32_t shift_blocks,
		uint32_t shift_bits
)
{
	int32_t		in_block_idx;
	uint32_t	out_block_idx;
	uint32_t	high_bits;
	uint32_t	block;
	uint32_t	low_bits;

	in_block_idx = result->length - 1;
	out_block_idx = result->length + shift_blocks;
	result->length = out_block_idx + 1;
	high_bits = 0;
	block = result->blocks[in_block_idx];
	low_bits = block >> (32 - shift_bits);
	while (in_block_idx > 0)
	{
		result->blocks[out_block_idx] = high_bits | low_bits;
		high_bits = block << shift_bits;
		block = result->blocks[--in_block_idx];
		low_bits = block >> (32 - shift_bits);
		--out_block_idx;
	}
	result->blocks[out_block_idx] = high_bits | low_bits;
	result->blocks[out_block_idx - 1] = block << shift_bits;
	zero_low_blocks(result, shift_blocks);
	if (result->blocks[result->length - 1] == 0)
		result->length--;
}

void		bi_shift_left(t_big_int *result, uint32_t shift)
{
	uint32_t	shift_blocks;
	uint32_t	shift_bits;

	shift_blocks = shift / 32;
	shift_bits = shift % 32;
	if (shift_bits == 0)
		shift_aligned(result, shift_blocks);
	else
		shift_not_aligned(result, shift_blocks, shift_bits);
}
