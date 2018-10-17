/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer_part3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:41:03 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 20:41:31 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

int		uintmax_to_buf(uintmax_t u, int base, int capitals, char **buf)
{
	static char	digs[] = "0123456789abcdef0123456789ABCDEF";
	int			length;

	if (u == 0)
	{
		**buf = digs[0];
		(*buf)--;
		return (1);
	}
	length = 0;
	while (u != 0)
	{
		**buf = digs[(u % base) + capitals];
		(*buf)--;
		u /= base;
		length++;
	}
	return (length);
}

char	*get_prefix_for_int(uintmax_t u, t_fms *fms, int base, int capitals)
{
	if (base == 2)
	{
		if (u == 0 || !fms->altfmt)
			return (0);
		return (capitals ? "0B" : "0b");
	}
	if (base == 8)
	{
		if (!fms->altfmt)
			return (0);
		else if (u == 0 && fms->precision == -1)
			return (0);
		return ("0");
	}
	else if (base == 16)
	{
		if (u == 0 || !fms->altfmt)
			return (0);
		return (capitals ? "0X" : "0x");
	}
	return (0);
}
