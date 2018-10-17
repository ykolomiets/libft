/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_core_start_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 14:49:51 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/06 14:49:53 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"
#include "libft.h"

#define LOG10_2 0.30102999566398119521373889472449

static void		set_start_value_for_unequal_margins
(
		t_dragon4_sup *sup,
		t_dragon4_arg *arg
)
{
	if (arg->exponent > 0)
	{
		bi_set_u64(&sup->scaled_value, 4 * arg->mantissa);
		bi_shift_left(&sup->scaled_value, (uint32_t)arg->exponent);
		bi_set_u32(&sup->scale, 4);
		bi_pow2(&sup->scaled_margin_low, (uint32_t)arg->exponent);
		bi_pow2(&sup->optional_margin_high, (uint32_t)arg->exponent + 1);
	}
	else
	{
		bi_set_u64(&sup->scaled_value, 4 * arg->mantissa);
		bi_pow2(&sup->scale, -arg->exponent + 2);
		bi_set_u32(&sup->scaled_margin_low, 1);
		bi_set_u32(&sup->optional_margin_high, 2);
	}
	sup->p_scaled_margin_high = &sup->optional_margin_high;
}

static void		set_start_value_for_not_unequal_margins
(
		t_dragon4_sup *sup,
		t_dragon4_arg *arg
)
{
	if (arg->exponent > 0)
	{
		bi_set_u64(&sup->scaled_value, 2 * arg->mantissa);
		bi_shift_left(&sup->scaled_value, (uint32_t)arg->exponent);
		bi_set_u32(&sup->scale, 2);
		bi_pow2(&sup->scaled_margin_low, (uint32_t)arg->exponent);
	}
	else
	{
		bi_set_u64(&sup->scaled_value, 2 * arg->mantissa);
		bi_pow2(&sup->scale, -arg->exponent + 1);
		bi_set_u32(&sup->scaled_margin_low, 1);
	}
	sup->p_scaled_margin_high = &sup->scaled_margin_low;
}

static void		adjust_depend_on_exponent(t_dragon4_sup *sup)
{
	t_big_int	temp;
	t_big_int	pow10;

	if (sup->digit_exponent > 0)
	{
		bi_mult_by_pow10(&temp, &sup->scale, (uint32_t)sup->digit_exponent);
		sup->scale = temp;
	}
	else if (sup->digit_exponent < 0)
	{
		bi_pow10(&pow10, -(sup->digit_exponent));
		bi_mult_bi_by_bi(&temp, &sup->scaled_value, &pow10);
		sup->scaled_value = temp;
		bi_mult_bi_by_bi(&temp, &sup->scaled_margin_low, &pow10);
		sup->scaled_margin_low = temp;
		if (sup->p_scaled_margin_high != &sup->scaled_margin_low)
			bi_mult_bi_by_2(sup->p_scaled_margin_high, &sup->scaled_margin_low);
	}
}

static int32_t	get_digit_exponent(t_dragon4_arg *arg)
{
	int32_t	digit_exponent;

	digit_exponent = (int32_t)(
			ft_ceil(((int32_t)arg->mantissa_high_bit_idx + arg->exponent)
					* LOG10_2 - 0.69));
	if (arg->cutoff_mode == CUTOFF_MODE_FRACTIONAL_LENGTH
		&& digit_exponent <= -(int32_t)arg->cutoff_number)
		digit_exponent = -(int32_t)arg->cutoff_number + 1;
	return (digit_exponent);
}

void			dragon4_set_start_value
(
		t_dragon4_sup *sup,
		t_dragon4_arg *arg
)
{
	if (arg->has_unequal_margins)
		set_start_value_for_unequal_margins(sup, arg);
	else
		set_start_value_for_not_unequal_margins(sup, arg);
	sup->digit_exponent = get_digit_exponent(arg);
	adjust_depend_on_exponent(sup);
	if (bi_compare(&sup->scaled_value, &sup->scale) >= 0)
		sup->digit_exponent++;
	else
	{
		bi_mult_bi_by_10_inplace(&sup->scaled_value);
		bi_mult_bi_by_10_inplace(&sup->scaled_margin_low);
		if (sup->p_scaled_margin_high != &sup->scaled_margin_low)
			bi_mult_bi_by_2(sup->p_scaled_margin_high, &sup->scaled_margin_low);
	}
}
