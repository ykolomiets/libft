/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_to_integer_conversion.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:35:27 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:36:51 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_TO_INTEGER_CONVERSION_H
# define FLOAT_TO_INTEGER_CONVERSION_H

# include "inttypes.h"

typedef union	u_float_union64
{
	double		floating_point;
	uint64_t	integer;
}				t_float_union64;

int				fu64_is_negative(t_float_union64 val);
uint32_t		fu64_get_exponent(t_float_union64 val);
uint64_t		fu64_get_mantissa(t_float_union64 val);

#endif
