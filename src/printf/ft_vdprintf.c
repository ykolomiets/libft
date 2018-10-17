/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:07:54 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:07:55 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf_core.h"
#include <unistd.h>

static int	print_to_stream(t_printf *options, char c)
{
	int	wrote;

	options->buffer[options->pos_in_buffer++] = c;
	if (options->pos_in_buffer == BUF_SIZE)
	{
		if ((wrote = write(options->fd, options->buffer, BUF_SIZE)) == -1)
			return (-1);
		options->printed += wrote;
		options->pos_in_buffer = 0;
		ft_bzero(options->buffer, BUF_SIZE);
	}
	return (0);
}

static int	flush_to_stream(t_printf *options)
{
	int	wrote;

	if ((wrote = write(options->fd, options->buffer,
			options->pos_in_buffer)) == -1)
		return (-1);
	options->printed += wrote;
	return (0);
}

int			ft_vdprintf(const int fd, const char *restrict fmt, va_list *ap)
{
	t_printf	options;
	int			res;

	options.fd = fd;
	options.pos_in_buffer = 0;
	ft_bzero(options.buffer, BUF_SIZE);
	options.putc = print_to_stream;
	options.flush = flush_to_stream;
	options.ap = ap;
	options.printed = 0;
	if ((res = printf_core(&options, fmt)))
		return (-1);
	return (options.printed);
}
