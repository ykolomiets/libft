/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:07:45 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:07:47 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_printf(const char *restrict fmt, ...)
{
	int			printed;
	va_list		ap;

	va_start(ap, fmt);
	printed = ft_vdprintf(1, fmt, &ap);
	va_end(ap);
	return (printed);
}
