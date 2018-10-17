/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchartobuf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:39:23 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:39:24 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

#define UTF8_2_BYTES_MASK 0xC0
#define UTF8_3_BYTES_MASK 0xE0
#define UTF8_4_BYTES_MASK 0xF0
#define UTF8_AUX_BYTE_MASK 0x80
#define SIX_BITS_MASK 0x3F
#define FIVE_BITS_MASK 0x1F
#define FOUR_BITS_MASK 0xF
#define THREE_BITS_MASK 0x6

int			wchar_length_in_bytes(wchar_t ch)
{
	if (ch < 0x80)
		return (1);
	if (ch < 0x800)
		return (2);
	if (ch < 0x10000)
		return (3);
	if (ch < 0x200000)
		return (4);
	return (0);
}

int			wchartobuf(wchar_t ch, char *buf)
{
	int	bytes;
	int	i;

	bytes = wchar_length_in_bytes(ch);
	if (bytes == 1)
		buf[0] = (char)ch;
	else if (bytes <= 4)
	{
		i = 0;
		while (i < bytes - 1)
		{
			buf[i++] = (ch & SIX_BITS_MASK) | UTF8_AUX_BYTE_MASK;
			ch >>= 6;
		}
		if (bytes == 2)
			buf[1] = (ch & FIVE_BITS_MASK) | UTF8_2_BYTES_MASK;
		else if (bytes == 3)
			buf[2] = (ch & FOUR_BITS_MASK) | UTF8_3_BYTES_MASK;
		else if (bytes == 4)
			buf[3] = (ch & FOUR_BITS_MASK) | UTF8_4_BYTES_MASK;
	}
	return (bytes);
}
