/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_addition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:54:42 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:54:43 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

static void	pickup_large_and_small
(
		t_bi_add_support *bi_add,
		t_big_int *left,
		t_big_int *right
)
{
	if (left->length > right->length)
	{
		bi_add->large = left;
		bi_add->small = right;
	}
	else
	{
		bi_add->small = left;
		bi_add->large = right;
	}
	bi_add->large_cur = bi_add->large->blocks;
	bi_add->large_end = bi_add->large_cur + bi_add->large->length;
	bi_add->small_cur = bi_add->small->blocks;
	bi_add->small_end = bi_add->small_cur + bi_add->small->length;
}

static void	sum_while_small
(
		t_bi_add_support *params,
		uint64_t *out_carry,
		uint32_t **result
)
{
	uint64_t	sum;
	uint64_t	carry;

	carry = 0;
	while (params->small_cur != params->small_end)
	{
		sum = (uint64_t)*params->small_cur + (uint64_t)*params->large_cur
				+ carry;
		carry = sum >> 32;
		**result = sum & 0xffffffff;
		++params->small_cur;
		++params->large_cur;
		++(*result);
	}
	*out_carry = carry;
}

void		bi_add
(
		t_big_int *result,
		t_big_int *left,
		t_big_int *right
)
{
	t_bi_add_support	params;
	uint64_t			sum;
	uint64_t			carry;
	uint32_t			*result_cur;

	pickup_large_and_small(&params, left, right);
	result_cur = result->blocks;
	sum_while_small(&params, &carry, &result_cur);
	while (params.large_cur != params.large_end)
	{
		sum = *params.large_cur + carry;
		carry = sum >> 32;
		*result_cur = sum & 0xffffffff;
		++params.large_cur;
		++result_cur;
	}
	if (carry != 0)
	{
		result->length = params.large->length + 1;
		*result_cur = 1;
	}
	else
	{
		result->length = params.large->length;
	}
}
