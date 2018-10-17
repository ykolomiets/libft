/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:07:39 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:07:42 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_dprintf(const int fd, const char *restrict fmt, ...)
{
	int			printed;
	va_list		ap;

	va_start(ap, fmt);
	printed = ft_vdprintf(fd, fmt, &ap);
	va_end(ap);
	return (printed);
}
