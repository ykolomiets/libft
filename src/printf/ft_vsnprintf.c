/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:07:59 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:08:01 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf_core.h"

static int	print_to_buf(t_printf *options, char c)
{
	options->external_buffer[options->pos_in_buffer++] = c;
	options->printed++;
	if (options->pos_in_buffer == options->external_buffer_size)
		return (1);
	return (0);
}

static int	flush_to_buf(t_printf *options)
{
	(void)options;
	return (0);
}

int			ft_vsnprintf
(
		char *buf,
		const int size,
		const char *restrict fmt,
		va_list *ap
)
{
	t_printf	options;

	options.ap = ap;
	options.external_buffer = buf;
	options.external_buffer_size = size;
	options.pos_in_buffer = 0;
	options.putc = print_to_buf;
	options.flush = flush_to_buf;
	options.printed = 0;
	printf_core(&options, fmt);
	return (options.printed);
}
