/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer_part2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:32:23 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 20:32:25 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include "libft.h"

static int	grl
(
	int buf_size,
	char sign_char,
	char *prefix,
	int precision
)
{
	int	length;

	length = buf_size;
	if (sign_char)
		length++;
	if (prefix)
		length += ft_strlen(prefix);
	if (precision > 0)
		length += precision;
	return (length);
}

static int	print_spacepad_sign_prefix
(
	t_printf *options,
	t_fms *fms,
	char sign_char,
	char *prefix
)
{
	int	print_res;

	if (fms->padc == ' ' && !fms->left_adjust)
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, ' ')))
				return (print_res);
	}
	if (sign_char)
		if ((print_res = options->putc(options, sign_char)))
			return (print_res);
	if (prefix)
		while (*prefix)
			if ((print_res = options->putc(options, *prefix++)))
				return (print_res);
	return (0);
}

static int	print_zeropad(t_printf *options, t_fms *fms)
{
	int	print_res;

	if (fms->padc == '0')
	{
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	}
	else
	{
		while (--fms->precision >= 0)
			if ((print_res = options->putc(options, '0')))
				return (print_res);
	}
	return (0);
}

static int	print_buf
(
	t_printf *options,
	char *buf_start,
	char *buf_end
)
{
	int	print_res;

	while (++buf_start != buf_end)
		if ((print_res = options->putc(options, *buf_start)))
			return (print_res);
	return (0);
}

int			print_num
(
	uintmax_t u,
	t_printf *options,
	t_fms *fms,
	t_int_options *int_opt
)
{
	char	buffer[INT_BUF_SIZE];
	char	*p;
	char	*prefix;
	int		str_len;
	int		print_res;

	prefix = get_prefix_for_int(u, fms, int_opt->base, int_opt->capitals);
	p = &buffer[INT_BUF_SIZE - 1];
	str_len = 0;
	if (u != 0 || fms->precision != 0)
		str_len = uintmax_to_buf(u, int_opt->base, int_opt->capitals, &p);
	fms->precision -= str_len;
	if (int_opt->base == 8 && fms->altfmt)
		fms->precision--;
	fms->length -= grl(str_len, int_opt->sign_char, prefix, fms->precision);
	if ((print_res = print_spacepad_sign_prefix(options, fms,
			int_opt->sign_char, prefix)))
		return (print_res);
	if ((print_res = print_zeropad(options, fms)))
		return (print_res);
	if ((print_res = print_buf(options, p, &buffer[INT_BUF_SIZE])))
		return (print_res);
	if ((print_res = print_left_adjust(options, fms)))
		return (print_res);
	return (0);
}
