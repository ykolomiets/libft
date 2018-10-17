/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:12:39 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 20:12:40 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include <unistd.h>

static void		get_base_register_sign(char spec, t_int_options *opt)
{
	if (spec == 'b' || spec == 'B')
		opt->base = 2;
	if (spec == 'd' || spec == 'D' || spec == 'i' || spec == 'u' || spec == 'U')
		opt->base = 10;
	else if (spec == 'x' || spec == 'X')
		opt->base = 16;
	else if (spec == 'o' || spec == 'O')
		opt->base = 8;
	if (spec == 'X' || spec == 'B')
		opt->capitals = 16;
	else
		opt->capitals = 0;
	if (spec == 'd' || spec == 'D' || spec == 'i')
		opt->is_signed = TRUE;
	else
		opt->is_signed = FALSE;
}

static intmax_t	get_signed_arg(va_list *ap, t_length_modifier length_modifier)
{
	intmax_t n;

	if (length_modifier == LM_NONE)
		n = va_arg(*ap, int);
	else if (length_modifier == LM_LONG)
		n = va_arg(*ap, long);
	else if (length_modifier == LM_LONG_LONG)
		n = va_arg(*ap, long long);
	else if (length_modifier == LM_SHORT)
		n = (short)va_arg(*ap, int);
	else if (length_modifier == LM_SHORT_SHORT)
		n = (signed char)va_arg(*ap, int);
	else if (length_modifier == LM_J)
		n = va_arg(*ap, intmax_t);
	else
		n = va_arg(*ap, ssize_t);
	return (n);
}

static int		print_signed_integer
(
		t_printf *options,
		t_fms *fms,
		t_int_options *int_opt
)
{
	intmax_t	n;
	uintmax_t	u;

	n = get_signed_arg(options->ap, fms->length_modifier);
	if (n >= 0)
	{
		u = n;
		int_opt->sign_char = fms->plus_sign;
	}
	else
	{
		u = -n;
		int_opt->sign_char = '-';
	}
	return (print_num(u, options, fms, int_opt));
}

static int		print_unsigned_integer
(
		t_printf *options,
		t_fms *fms,
		t_int_options *int_opt
)
{
	uintmax_t	u;

	if (fms->length_modifier == LM_NONE)
		u = va_arg(*options->ap, unsigned);
	else if (fms->length_modifier == LM_LONG_LONG)
		u = va_arg(*options->ap, unsigned long long);
	else if (fms->length_modifier == LM_LONG)
		u = va_arg(*options->ap, unsigned long);
	else if (fms->length_modifier == LM_SHORT)
		u = (unsigned short)va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_SHORT_SHORT)
		u = (unsigned char)va_arg(*options->ap, int);
	else if (fms->length_modifier == LM_J)
		u = va_arg(*options->ap, uintmax_t);
	else
		u = va_arg(*options->ap, size_t);
	int_opt->sign_char = 0;
	return (print_num(u, options, fms, int_opt));
}

int				print_integer(t_printf *options, t_fms *fms)
{
	t_int_options	int_opt;

	if (fms->precision != -1)
		fms->padc = ' ';
	get_base_register_sign(fms->specifier, &int_opt);
	if (int_opt.is_signed)
		return (print_signed_integer(options, fms, &int_opt));
	else
		return (print_unsigned_integer(options, fms, &int_opt));
}
