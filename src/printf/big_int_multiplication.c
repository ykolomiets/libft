/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_multiplication.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:23:56 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:23:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

static void	pickup_large_and_small
(
		t_bi_mult_support *mult_params,
		t_big_int *left,
		t_big_int *right
)
{
	if (left->length > right->length)
	{
		mult_params->large = left;
		mult_params->small = right;
	}
	else
	{
		mult_params->small = left;
		mult_params->large = right;
	}
	mult_params->small_beg = mult_params->small->blocks;
	mult_params->small_end = mult_params->small->blocks
			+ mult_params->small->length;
	mult_params->large_beg = mult_params->large->blocks;
	mult_params->large_end = mult_params->large->blocks
			+ mult_params->large->length;
}

static void	clear_result
(
		t_big_int *result,
		uint32_t length
)
{
	uint32_t	i;

	i = 0;
	while (i < length)
		result->blocks[i++] = 0;
}

static void	mult_core
(
		t_bi_mult_support *params,
		uint32_t multiplier,
		uint32_t *res_start
)
{
	uint32_t *large_cur;
	uint32_t *res_cur;
	uint64_t carry;
	uint64_t product;

	large_cur = params->large_beg;
	res_cur = res_start;
	carry = 0;
	while (large_cur != params->large_end)
	{
		product = (*res_cur)
				+ (*large_cur) * (uint64_t)(multiplier) + carry;
		carry = product >> 32;
		*res_cur = product & 0xffffffff;
		large_cur++;
		res_cur++;
	}
	*res_cur = (uint32_t)(carry & 0xffffffff);
}

void		bi_mult_bi_by_bi
(
		t_big_int *result,
		t_big_int *left,
		t_big_int *right
)
{
	t_bi_mult_support	params;
	uint32_t			max_result_length;
	uint32_t			*small_cur;
	uint32_t			*res_start;

	pickup_large_and_small(&params, left, right);
	max_result_length = params.large->length + params.small->length;
	clear_result(result, max_result_length);
	res_start = result->blocks;
	small_cur = params.small_beg;
	while (small_cur != params.small_end)
	{
		if (*small_cur)
			mult_core(&params, *small_cur, res_start);
		small_cur++;
		res_start++;
	}
	if (max_result_length > 0 && result->blocks[max_result_length - 1] == 0)
		result->length = max_result_length - 1;
	else
		result->length = max_result_length;
}
