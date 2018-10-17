/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:51:27 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:51:29 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

#define POINTER_BUF_SIZE (sizeof(void *) * 2)

static int	num_to_buffer(long long u, char **buf)
{
	static char	digs[] = "0123456789abcdef";
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
		**buf = digs[u % 16];
		(*buf)--;
		u /= 16;
		length++;
	}
	return (length);
}

static int	print_pad_and_prefix(t_printf *options, t_fms *fms)
{
	int	print_res;

	if (!fms->left_adjust && fms->padc == ' ')
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	if ((print_res = options->putc(options, '0')))
		return (print_res);
	if ((print_res = options->putc(options, 'x')))
		return (print_res);
	if (!fms->left_adjust && fms->padc == '0')
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	return (0);
}

int			print_pointer(t_printf *options, t_fms *fms)
{
	int			print_res;
	long long	pointer;
	char		buf[POINTER_BUF_SIZE];
	char		*p;
	int			size;

	pointer = (long long)va_arg(*options->ap, void *);
	p = &buf[POINTER_BUF_SIZE - 1];
	size = 0;
	if (!(pointer == 0 && fms->precision == 0))
		size = num_to_buffer(pointer, &p);
	fms->precision -= size;
	fms->length -= (2 + size + (fms->precision > 0 ? fms->precision : 0));
	if ((print_res = print_pad_and_prefix(options, fms)))
		return (print_res);
	while (--fms->precision >= 0)
		if ((print_res = options->putc(options, '0')))
			return (print_res);
	while (++p != &buf[POINTER_BUF_SIZE])
		if ((print_res = options->putc(options, *p)))
			return (print_res);
	print_left_adjust(options, fms);
	return (0);
}
