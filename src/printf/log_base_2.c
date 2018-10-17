/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_base_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:04:40 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:04:41 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"

#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n

uint32_t	log_base_2_uint32(uint32_t val)
{
	static const uint8_t	log_table[256] = {
		0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		LT(4),
		LT(5), LT(5),
		LT(6), LT(6), LT(6), LT(6),
		LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7),
	};
	uint32_t				temp;

	temp = val >> 24;
	if (temp)
		return (24 + log_table[temp]);
	temp = val >> 16;
	if (temp)
		return (16 + log_table[temp]);
	temp = val >> 8;
	if (temp)
		return (8 + log_table[temp]);
	return (log_table[val]);
}

uint32_t	log_base_2_uint64(uint64_t val)
{
	uint64_t	temp;

	temp = val >> 32;
	if (temp)
		return (32 + log_base_2_uint32((uint32_t)temp));
	return (log_base_2_uint32((uint32_t)val));
}
