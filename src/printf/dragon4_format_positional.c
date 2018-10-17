/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_format_positional.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:10:19 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:10:20 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"
#include "libft.h"

static t_dragon4_arg	form_dragon4_arg
(
		t_format_arg *arg,
		int32_t *print_exponent,
		int precision
)
{
	t_dragon4_arg	dragon4_arg;

	dragon4_arg.mantissa = arg->mantissa;
	dragon4_arg.exponent = arg->exponent;
	dragon4_arg.out_buffer = arg->out_buffer;
	dragon4_arg.buffer_size = arg->buffer_size - 1;
	dragon4_arg.out_exponent = print_exponent;
	if (precision < 0)
	{
		dragon4_arg.mantissa_high_bit_idx = arg->mantissa_high_bit_idx;
		dragon4_arg.has_unequal_margins = arg->has_unequal_margins;
		dragon4_arg.cutoff_mode = CUTOFF_MODE_UNIQUE;
		dragon4_arg.cutoff_number = 0;
	}
	else
	{
		dragon4_arg.mantissa_high_bit_idx = arg->mantissa_high_bit_idx;
		dragon4_arg.has_unequal_margins = arg->has_unequal_margins;
		dragon4_arg.cutoff_mode = CUTOFF_MODE_FRACTIONAL_LENGTH;
		dragon4_arg.cutoff_number = arg->precision;
	}
	return (dragon4_arg);
}

static void				help1
(
		t_format_arg *arg,
		int32_t print_exponent,
		uint32_t *num_print_digits,
		uint32_t *num_fraction_digits
)
{
	uint32_t	num_whole_digits;
	uint32_t	max_fraction_digits;

	num_whole_digits = print_exponent + 1;
	if (*num_print_digits < num_whole_digits)
	{
		if (num_whole_digits > arg->buffer_size - 1)
			num_whole_digits = arg->buffer_size - 1;
		while (*num_print_digits < num_whole_digits)
			arg->out_buffer[(*num_print_digits)++] = '0';
	}
	else if (*num_print_digits > num_whole_digits)
	{
		*num_fraction_digits = *num_print_digits - num_whole_digits;
		max_fraction_digits = (arg->buffer_size - 1) - num_whole_digits - 1;
		if (*num_fraction_digits > max_fraction_digits)
			*num_fraction_digits = max_fraction_digits;
		ft_memmove(arg->out_buffer + num_whole_digits + 1,
					arg->out_buffer + num_whole_digits,
					*num_fraction_digits);
		arg->out_buffer[num_whole_digits] = '.';
		*num_print_digits = num_whole_digits + 1 + *num_fraction_digits;
	}
}

static void				set_zero_and_point
(
		t_format_arg *arg,
		uint32_t *num_print_digits
)
{
	if (arg->buffer_size - 1 > 1)
	{
		arg->out_buffer[1] = '.';
		(*num_print_digits)++;
	}
	if (arg->buffer_size - 1 > 0)
	{
		arg->out_buffer[0] = '0';
		(*num_print_digits)++;
	}
}

static void				help2
(
		t_format_arg *arg,
		int32_t print_exponent,
		uint32_t *num_print_digits,
		uint32_t *num_fraction_digits
)
{
	uint32_t	num_fraction_zeroes;
	uint32_t	max_fraction_zeroes;
	uint32_t	digits_start_idx;
	uint32_t	max_fraction_digits;

	if (arg->buffer_size - 1 > 2)
	{
		num_fraction_zeroes = (uint32_t)(-print_exponent - 1);
		max_fraction_zeroes = (arg->buffer_size - 1) - 2;
		if (num_fraction_zeroes > max_fraction_zeroes)
			num_fraction_zeroes = max_fraction_zeroes;
		digits_start_idx = 2 + num_fraction_zeroes;
		*num_fraction_digits = *num_print_digits;
		max_fraction_digits = (arg->buffer_size - 1) - digits_start_idx;
		if (*num_fraction_digits > max_fraction_digits)
			*num_fraction_digits = max_fraction_digits;
		ft_memmove(arg->out_buffer + digits_start_idx,
				arg->out_buffer, *num_fraction_digits);
		ft_memset(arg->out_buffer + 2, '0', digits_start_idx - 2);
		*num_fraction_digits += num_fraction_zeroes;
		*num_print_digits = *num_fraction_digits;
	}
	set_zero_and_point(arg, num_print_digits);
}

uint32_t				format_positional(t_format_arg arg)
{
	int32_t			print_exponent;
	uint32_t		num_print_digits;
	uint32_t		num_fraction_digits;
	uint32_t		total_digits;

	num_print_digits = dragon4(
			form_dragon4_arg(&arg, &print_exponent, arg.precision));
	num_fraction_digits = 0;
	if (print_exponent >= 0)
		help1(&arg, print_exponent, &num_print_digits, &num_fraction_digits);
	else
		help2(&arg, print_exponent, &num_print_digits, &num_fraction_digits);
	if (arg.precision > (int32_t)num_fraction_digits
		&& num_print_digits < (arg.buffer_size - 1))
	{
		if (num_fraction_digits == 0)
			arg.out_buffer[num_print_digits++] = '.';
		total_digits = num_print_digits + (arg.precision - num_fraction_digits);
		if (total_digits > arg.buffer_size - 1)
			total_digits = arg.buffer_size - 1;
		while (num_print_digits < total_digits)
			arg.out_buffer[num_print_digits++] = '0';
	}
	arg.out_buffer[num_print_digits] = '\0';
	return (num_print_digits);
}
