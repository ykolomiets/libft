/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:07:50 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:07:51 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_snprintf(char *restrict buf, const int size, const char *fmt, ...)
{
	int		printed;
	va_list	ap;

	va_start(ap, fmt);
	printed = ft_vsnprintf(buf, size, fmt, &ap);
	va_end(ap);
	return (printed);
}
