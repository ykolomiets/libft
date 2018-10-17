/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_power_of_10.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:16:56 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:19:21 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "big_int.h"

#define P12_OF_10PART1 0, 0, 0, 0, 0x2e953e01, 0x03df9909, 0x0f1538fd
#define P12_OF_10PART2 0x2374e42f, 0xd3cff5ec, 0xc404dc08, 0xbccdb0da
#define P12_OF_10PART3 0xa6337f19, 0xe91f2603, 0x0000024e

#define P13_OF_10PART1 0, 0, 0, 0, 0, 0, 0, 0
#define P13_OF_10PART2 0x982e7c01, 0xbed3875b, 0xd8d99f72, 0x12152f87
#define P13_OF_10PART3 0x6bde50c6, 0xcf4a6e70, 0xd595d80f, 0x26b2716e
#define P13_OF_10PART4 0xadc666b0, 0x1d153624, 0x3c42d35a, 0x63ff540e
#define P13_OF_10PART5 0xcc5573c0, 0x65f9ef17, 0x55bc28f2, 0x80dcc7f7
#define P13_OF_10PART6 0xf46eeddc, 0x5fdcefce, 0x000553f7

uint32_t			get_pow10_uint32(uint32_t pow)
{
	static uint32_t power_of_10[] = {
			1,
			10,
			100,
			1000,
			10000,
			100000,
			1000000,
			10000000,
	};

	return (power_of_10[pow]);
}

t_big_int			*get_pow10_big_int(uint32_t pow)
{
	static t_big_int	power_of_10[6] = {
	{1, {100000000 } },
	{2, {0x6fc10000, 0x002386f2 } },
	{4, {0, 0x85acef81, 0x2d6d415b, 0x000004ee} },
	{7, {0, 0, 0xbf6a1f01, 0x6e38ed64, 0xdaa797ed, 0xe93ff9f4, 0x00184f03}},
	{14, {P12_OF_10PART1, P12_OF_10PART2, P12_OF_10PART3}},
	{27, {P13_OF_10PART1, P13_OF_10PART2, P13_OF_10PART3,
			P13_OF_10PART4, P13_OF_10PART5, P13_OF_10PART6 }}};

	return (&power_of_10[pow]);
}
