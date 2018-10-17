/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_format_scientific.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:10:23 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:10:25 by ykolomie         ###   ########.fr       */
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
	dragon4_arg.mantissa_high_bit_idx = arg->mantissa_high_bit_idx;
	dragon4_arg.has_unequal_margins = arg->has_unequal_margins;
	dragon4_arg.out_buffer = arg->out_buffer;
	dragon4_arg.buffer_size = arg->buffer_size;
	dragon4_arg.out_exponent = print_exponent;
	if (precision < 0)
	{
		dragon4_arg.cutoff_mode = CUTOFF_MODE_UNIQUE;
		dragon4_arg.cutoff_number = 0;
	}
	else
	{
		dragon4_arg.cutoff_mode = CUTOFF_MODE_TOTAL_LENGTH;
		dragon4_arg.cutoff_number = arg->precision + 1;
	}
	return (dragon4_arg);
}

static void				insert_decimal_point
(
		t_format_arg *arg,
		uint32_t *num_fraction_digits,
		char **cur_out
)
{
	uint32_t	max_fraction_digits;

	if (*num_fraction_digits > 0 && arg->buffer_size > 1)
	{
		max_fraction_digits = arg->buffer_size - 2;
		if (*num_fraction_digits > max_fraction_digits)
			*num_fraction_digits = max_fraction_digits;
		ft_memmove(*cur_out + 1, *cur_out, *num_fraction_digits);
		(*cur_out)[0] = '.';
		(*cur_out) += (1 + *num_fraction_digits);
		arg->buffer_size -= (1 + *num_fraction_digits);
	}
}

static void				add_trailing_zeroes
(
		t_format_arg *arg,
		uint32_t num_fraction_digits,
		char **cur_out
)
{
	uint32_t	num_zeroes;
	char		*end;

	if (arg->precision > (int32_t)num_fraction_digits && arg->buffer_size > 1)
	{
		if (num_fraction_digits == 0)
		{
			**cur_out = '.';
			(*cur_out)++;
			arg->buffer_size--;
		}
		num_zeroes = arg->precision - num_fraction_digits;
		if (num_zeroes > arg->buffer_size - 1)
			num_zeroes = arg->buffer_size - 1;
		end = *cur_out + num_zeroes;
		while (*cur_out < end)
		{
			**cur_out = '0';
			(*cur_out)++;
		}
	}
}

static void				add_exponent
(
		t_format_arg *arg,
		int32_t print_exponent,
		char **cur_out
)
{
	char		exponent_buffer[5];
	uint32_t	parts[3];
	uint32_t	i;

	exponent_buffer[0] = arg->is_upper_case ? 'E' : 'e';
	if (print_exponent >= 0)
		exponent_buffer[1] = '+';
	else
	{
		exponent_buffer[1] = '-';
		print_exponent = -print_exponent;
	}
	parts[0] = (uint32_t)(print_exponent / 100);
	parts[1] = (print_exponent - parts[0] * 100) / 10;
	parts[2] = (print_exponent - parts[0] * 100 - parts[1] * 10);
	i = 2;
	if (parts[0])
		exponent_buffer[i++] = (char)('0' + parts[0]);
	exponent_buffer[i++] = (char)('0' + parts[1]);
	exponent_buffer[i++] = (char)('0' + parts[2]);
	ft_memcpy(*cur_out, exponent_buffer, i);
	*cur_out += i;
	arg->buffer_size -= i;
}

uint32_t				format_scientific(t_format_arg arg)
{
	int32_t			print_exponent;
	uint32_t		num_print_digits;
	uint32_t		num_fraction_digits;
	char			*cur_out;

	num_print_digits = dragon4(
			form_dragon4_arg(&arg, &print_exponent, arg.precision));
	cur_out = arg.out_buffer;
	if (arg.buffer_size > 1)
	{
		cur_out++;
		arg.buffer_size--;
	}
	num_fraction_digits = num_print_digits - 1;
	insert_decimal_point(&arg, &num_fraction_digits, &cur_out);
	add_trailing_zeroes(&arg, num_fraction_digits, &cur_out);
	add_exponent(&arg, print_exponent, &cur_out);
	*cur_out = '\0';
	return ((uint32_t)(cur_out - arg.out_buffer));
}
