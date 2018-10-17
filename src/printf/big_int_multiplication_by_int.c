/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_multiplication_by_int.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:36:06 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:36:08 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

void		bi_mult_bi_by_uint32
(
		t_big_int *result,
		t_big_int *left,
		uint32_t right
)
{
	uint32_t	carry;
	uint32_t	*res_cur;
	uint32_t	*left_cur;
	uint32_t	*left_end;
	uint64_t	product;

	carry = 0;
	res_cur = result->blocks;
	left_cur = left->blocks;
	left_end = left_cur + left->length;
	while (left_cur != left_end)
	{
		product = (uint64_t)(*left_cur) * right + carry;
		*res_cur = (uint32_t)(product & 0xffffffff);
		carry = product >> 32;
		left_cur++;
		res_cur++;
	}
	if (carry)
	{
		*res_cur = (uint32_t)carry;
		result->length = left->length + 1;
	}
	else
		result->length = left->length;
}

void		bi_mult_bi_by_2
(
		t_big_int *result,
		t_big_int *in
)
{
	uint32_t	carry;
	uint32_t	*res_cur;
	uint32_t	*in_cur;
	uint32_t	*in_end;
	uint32_t	cur;

	carry = 0;
	res_cur = result->blocks;
	in_cur = in->blocks;
	in_end = in_cur + in->length;
	while (in_cur != in_end)
	{
		cur = *in_cur;
		*res_cur = (cur << 1) | carry;
		carry = cur >> 31;
		in_cur++;
		res_cur++;
	}
	if (carry)
	{
		*res_cur = carry;
		result->length = in->length + 1;
	}
	else
		result->length = in->length;
}

void		bi_mult_bi_by_2_inplace(t_big_int *result)
{
	uint32_t	carry;
	uint32_t	*res_cur;
	uint32_t	*res_end;
	uint32_t	cur;

	carry = 0;
	res_cur = result->blocks;
	res_end = res_cur + result->length;
	while (res_cur != res_end)
	{
		cur = *res_cur;
		*res_cur = (cur << 1) | carry;
		carry = cur >> 31;
		res_cur++;
	}
	if (carry)
	{
		*res_cur = carry;
		result->length++;
	}
}

void		bi_mult_bi_by_10_inplace(t_big_int *result)
{
	uint32_t	carry;
	uint32_t	*res_cur;
	uint32_t	*res_end;
	uint64_t	product;

	carry = 0;
	res_cur = result->blocks;
	res_end = res_cur + result->length;
	while (res_cur != res_end)
	{
		product = (uint64_t)(*res_cur) * 10ull + carry;
		*res_cur = (uint32_t)(product & 0xffffffff);
		carry = product >> 32;
		res_cur++;
	}
	if (carry)
	{
		*res_cur = carry;
		result->length++;
	}
}
