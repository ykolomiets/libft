/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:23:04 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/06 13:23:07 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "float_to_integer_conversion.h"

double		my_ceil(double d)
{
	t_float_union64	input;
	t_float_union64	output;
	int32_t			exponent;
	uint32_t		fractional_bits;

	input.floating_point = d;
	exponent = fu64_get_exponent(input) - 1023;
	if (exponent < 0)
		return (d > 0);
	fractional_bits = 52 - exponent;
	if (fractional_bits <= 0)
		return (d);
	output.integer = input.integer & (0xffffffffffffffff << fractional_bits);
	if (d > 0 && output.integer != input.integer)
		output.floating_point++;
	return (output.floating_point);
}
