/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float64_to_integer_conversion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:30:08 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:30:10 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float_to_integer_conversion.h"

int				fu64_is_negative(t_float_union64 val)
{
	return ((val.integer >> 63) != 0);
}

uint32_t		fu64_get_exponent(t_float_union64 val)
{
	return ((val.integer >> 52) & 0x7FF);
}

uint64_t		fu64_get_mantissa(t_float_union64 val)
{
	return (val.integer & 0xFFFFFFFFFFFFFull);
}
