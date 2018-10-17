/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:02:58 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:03:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include "libft.h"
#include <wchar.h>

static int	print_pad(t_printf *options, t_fms *fms)
{
	int		print_res;

	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	return (0);
}

static int	print_buf(t_printf *options, char *buf, int len)
{
	int	print_res;

	while (--len >= 0)
		if ((print_res = options->putc(options, buf[len])))
			return (print_res);
	return (0);
}

int			print_char(t_printf *options, t_fms *fms)
{
	wchar_t	wc;
	int		print_res;
	char	buf[4];
	int		len;

	if (fms->length_modifier == LM_LONG)
	{
		wc = (wchar_t)va_arg(*options->ap, wint_t);
		len = wchartobuf(wc, buf);
	}
	else
	{
		buf[0] = va_arg(*options->ap, int);
		len = 1;
	}
	fms->length -= len;
	if ((print_res = print_pad(options, fms)))
		return (print_res);
	if ((print_res = print_buf(options, buf, len)))
		return (print_res);
	if ((print_res = print_left_adjust(options, fms)))
		return (print_res);
	return (0);
}
