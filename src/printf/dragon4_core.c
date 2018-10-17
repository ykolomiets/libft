/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:10:14 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:10:16 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"

static int32_t	get_cutoff_exponent
(
	t_dragon4_arg *arg,
	int32_t digit_exponent
)
{
	int32_t	cutoff_exponent;
	int32_t	desired_cutoff_exponent;

	cutoff_exponent = digit_exponent - arg->buffer_size;
	if (arg->cutoff_mode == CUTOFF_MODE_TOTAL_LENGTH)
	{
		desired_cutoff_exponent = digit_exponent - (int32_t)arg->cutoff_number;
		if (desired_cutoff_exponent > cutoff_exponent)
			cutoff_exponent = desired_cutoff_exponent;
	}
	else if (arg->cutoff_mode == CUTOFF_MODE_FRACTIONAL_LENGTH)
	{
		desired_cutoff_exponent = -(int32_t)arg->cutoff_number;
		if (desired_cutoff_exponent > cutoff_exponent)
			cutoff_exponent = desired_cutoff_exponent;
	}
	return (cutoff_exponent);
}

static void		prepare_for_division(t_dragon4_sup *sup)
{
	uint32_t	hi_block;
	uint32_t	hi_block_log2;
	uint32_t	shift;

	hi_block = sup->scale.blocks[sup->scale.length - 1];
	if (hi_block < 8 || hi_block > 429496729)
	{
		hi_block_log2 = log_base_2_uint32(hi_block);
		shift = (32 + 27 - hi_block_log2) % 32;
		bi_shift_left(&sup->scale, shift);
		bi_shift_left(&sup->scaled_value, shift);
		bi_shift_left(&sup->scaled_margin_low, shift);
		if (sup->p_scaled_margin_high != &sup->scaled_margin_low)
			bi_mult_bi_by_2(sup->p_scaled_margin_high, &sup->scaled_margin_low);
	}
}

static uint32_t	output_main_part_unique
(
	t_dragon4_sup *sup,
	char **cur_digit
)
{
	uint32_t	output_digit;
	t_big_int	scaled_value_high;

	while (1)
	{
		sup->digit_exponent--;
		output_digit = bi_divide_with_remainder_maxquotient9(
				&sup->scaled_value, &sup->scale);
		bi_add(&scaled_value_high, &sup->scaled_value,
				sup->p_scaled_margin_high);
		sup->low = bi_compare(&sup->scaled_value, &sup->scaled_margin_low) < 0;
		sup->high = bi_compare(&scaled_value_high, &sup->scale) > 0;
		if (sup->low || sup->high
			|| (sup->digit_exponent == sup->cutoff_exponent))
			break ;
		**cur_digit = (char)('0' + output_digit);
		(*cur_digit)++;
		bi_mult_bi_by_10_inplace(&sup->scaled_value);
		bi_mult_bi_by_10_inplace(&sup->scaled_margin_low);
		if (sup->p_scaled_margin_high != &sup->scaled_margin_low)
			bi_mult_bi_by_2(sup->p_scaled_margin_high, &sup->scaled_margin_low);
	}
	return (output_digit);
}

static uint32_t	output_main_part_not_unique
(
	t_dragon4_sup *sup,
	char **cur_digit
)
{
	uint32_t	output_digit;

	sup->low = 0;
	sup->high = 0;
	while (1)
	{
		sup->digit_exponent--;
		output_digit = bi_divide_with_remainder_maxquotient9(
				&sup->scaled_value, &sup->scale);
		if (bi_is_zero(&sup->scaled_value)
			|| (sup->digit_exponent == sup->cutoff_exponent))
			break ;
		**cur_digit = (char)('0' + output_digit);
		(*cur_digit)++;
		bi_mult_bi_by_10_inplace(&sup->scaled_value);
	}
	return (output_digit);
}

uint32_t		dragon4(t_dragon4_arg arg)
{
	char			*cur_digit;
	t_dragon4_sup	sup;
	uint32_t		last_digit;

	if (arg.mantissa == 0)
	{
		arg.out_buffer[0] = '0';
		*arg.out_exponent = 0;
		return (1);
	}
	cur_digit = arg.out_buffer;
	dragon4_set_start_value(&sup, &arg);
	sup.cutoff_exponent = get_cutoff_exponent(&arg, sup.digit_exponent);
	*arg.out_exponent = sup.digit_exponent - 1;
	prepare_for_division(&sup);
	if (arg.cutoff_mode == CUTOFF_MODE_UNIQUE)
		last_digit = output_main_part_unique(&sup, &cur_digit);
	else
		last_digit = output_main_part_not_unique(&sup, &cur_digit);
	dragon4_apply_rounding(&sup, &arg, last_digit, &cur_digit);
	return ((uint32_t)(cur_digit - arg.out_buffer));
}
