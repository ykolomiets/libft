/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:42:58 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:42:59 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

static void	set_default_fms(t_fms *fms)
{
	fms->padc = ' ';
	fms->altfmt = FALSE;
	fms->left_adjust = FALSE;
	fms->plus_sign = 0;
	fms->length_modifier = LM_NONE;
	fms->specifier = 0;
	fms->specifier_type = ST_NONE;
	fms->length = 0;
	fms->precision = -1;
}

static int	parse_fms(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	if (c == '\0')
		fms->specifier_type = ST_NULL_TERNINATOR;
	while (c)
	{
		c = **fmt;
		if (is_flag(c))
			parse_flag(fmt, fms);
		else if (is_length_start(c))
			parse_length(fmt, fms, ap);
		else if (is_precision_start(c))
			parse_precision(fmt, fms, ap);
		else if (is_length_modifier_start(c))
			parse_length_modifier(fmt, fms);
		else
		{
			parse_specifier(fmt, fms);
			break ;
		}
	}
	return (0);
}

static int	print_specifier(t_printf *options, t_fms *fms)
{
	t_specifier_type	spec;

	spec = fms->specifier_type;
	if (spec == ST_PERCENT)
		return (print_percent(options, fms));
	else if (spec == ST_INTEGER)
		return (print_integer(options, fms));
	else if (spec == ST_FLOAT)
		return (print_float(options, fms));
	else if (spec == ST_CHARACTER)
		return (print_char(options, fms));
	else if (spec == ST_STRING)
		return (print_string(options, fms));
	else if (spec == ST_POINTER)
		return (print_pointer(options, fms));
	else if (spec == ST_NONE)
		return (print_none_specifier(options, fms));
	return (0);
}

int			printf_core(t_printf *options, const char *fmt)
{
	int		res;
	char	c;
	t_fms	fms;

	while ((c = *fmt++) != '\0')
	{
		if (c == '%')
		{
			set_default_fms(&fms);
			parse_fms(&fmt, &fms, options->ap);
			if ((res = print_specifier(options, &fms)))
				return (res);
		}
		else
		{
			if ((res = options->putc(options, c)))
				return (res);
		}
	}
	options->flush(options);
	return (0);
}
