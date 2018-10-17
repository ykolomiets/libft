/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:50:14 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 19:50:15 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include "libft.h"
#include <limits.h>

static int	get_wchar_string_length(wchar_t *str, int precision)
{
	int		str_len;
	int		ch_len;

	str_len = 0;
	while (*str != L'\0' && str_len < precision)
	{
		ch_len = wchar_length_in_bytes(*str);
		if (str_len + ch_len <= precision)
			str_len += ch_len;
		str++;
	}
	return (str_len);
}

static int	print_wchar_string_core(t_printf *options, t_fms *fms, wchar_t *str)
{
	int		len;
	char	buf[4];
	int		print_res;

	while (*str != L'\0')
	{
		len = wchartobuf(*str++, buf);
		if (len > fms->precision)
			break ;
		fms->precision -= len;
		while (--len >= 0)
			if ((print_res = options->putc(options, buf[len])))
				return (print_res);
	}
	return (0);
}

static int	print_wchar_string(t_printf *options, t_fms *fms)
{
	wchar_t	*str;
	int		print_res;

	if (!(str = va_arg(*options->ap, wchar_t *)))
		str = L"(null)";
	fms->length -= get_wchar_string_length(str, fms->precision);
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	if ((print_res = print_wchar_string_core(options, fms, str)))
		return (print_res);
	print_left_adjust(options, fms);
	return (0);
}

static int	print_char_string(t_printf *options, t_fms *fms)
{
	int		print_res;
	int		str_len;
	char	*p;

	if (!(p = va_arg(*options->ap, char *)))
		p = "(null)";
	str_len = 0;
	while (p[str_len] != '\0' && str_len < fms->precision)
		str_len++;
	fms->length -= str_len;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	while (*p != '\0' && --fms->precision >= 0)
		if ((print_res = options->putc(options, *p++)))
			return (print_res);
	print_left_adjust(options, fms);
	return (0);
}

int			print_string(t_printf *options, t_fms *fms)
{
	if (fms->precision == -1)
		fms->precision = INT_MAX;
	if (fms->length_modifier == LM_LONG)
		return (print_wchar_string(options, fms));
	else
		return (print_char_string(options, fms));
}
