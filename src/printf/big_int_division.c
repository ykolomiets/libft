/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_division.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:58:05 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:58:06 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

static void		divide_out_estimated_quotient
(
		t_big_int *dividend,
		t_big_int *divisor,
		uint32_t quotient
)
{
	t_bi_div_support	div_sup;
	uint32_t			*final_divisor_block;
	uint32_t			*divisor_cur;
	uint32_t			*dividend_cur;

	final_divisor_block = divisor->blocks + divisor->length - 1;
	divisor_cur = divisor->blocks;
	dividend_cur = dividend->blocks;
	div_sup.borrow = 0;
	div_sup.carry = 0;
	while (divisor_cur <= final_divisor_block)
	{
		div_sup.product = (uint64_t)(*divisor_cur)
				* (uint64_t)quotient + div_sup.carry;
		div_sup.carry = div_sup.product >> 32;
		div_sup.difference = (uint64_t)(*dividend_cur)
				- (div_sup.product & 0xffffffff) - div_sup.borrow;
		div_sup.borrow = (div_sup.difference >> 32) & 1;
		*dividend_cur = div_sup.difference & 0xffffffff;
		divisor_cur++;
		dividend_cur++;
	}
	while (dividend->length > 0 && dividend->blocks[dividend->length - 1] == 0)
		dividend->length--;
}

static void		substract_divisor
(
		t_big_int *dividend,
		t_big_int *divisor
)
{
	uint32_t	*final_divisor_block;
	uint32_t	*divisor_cur;
	uint32_t	*dividend_cur;
	uint64_t	borrow;
	uint64_t	difference;

	final_divisor_block = divisor->blocks + divisor->length - 1;
	divisor_cur = divisor->blocks;
	dividend_cur = dividend->blocks;
	borrow = 0;
	while (divisor_cur <= final_divisor_block)
	{
		difference = (uint64_t)(*dividend_cur)
				- (uint64_t)(*divisor_cur) - borrow;
		borrow = (difference >> 32) & 1;
		*dividend_cur = difference & 0xffffffff;
		divisor_cur++;
		dividend_cur++;
	}
	while (dividend->length > 0 && dividend->blocks[dividend->length - 1] == 0)
		dividend->length--;
}

uint32_t		bi_divide_with_remainder_maxquotient9
(
		t_big_int *dividend,
		t_big_int *divisor
)
{
	uint32_t	*final_divisor_block;
	uint32_t	*final_dividend_block;
	uint32_t	quotient;

	if (dividend->length < divisor->length)
		return (0);
	final_divisor_block = divisor->blocks + divisor->length - 1;
	final_dividend_block = dividend->blocks + dividend->length - 1;
	quotient = *final_dividend_block / (*final_divisor_block + 1);
	if (quotient != 0)
		divide_out_estimated_quotient(dividend, divisor, quotient);
	if (bi_compare(dividend, divisor) >= 0)
	{
		quotient++;
		substract_divisor(dividend, divisor);
	}
	return (quotient);
}
