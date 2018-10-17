/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:06:32 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:06:34 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

int		is_flag(char c)
{
	if (c == '#' || c == ' ' || c == '0' || c == '+' || c == '-')
		return (1);
	return (0);
}

void	parse_flag(const char **fmt, t_fms *fms)
{
	char	c;

	c = **fmt;
	if (c == '#')
		fms->altfmt = TRUE;
	else if (**fmt == '-')
	{
		fms->left_adjust = TRUE;
		fms->padc = ' ';
	}
	else if (c == '+')
		fms->plus_sign = '+';
	else if (c == ' ' && !fms->plus_sign)
		fms->plus_sign = ' ';
	else if (c == '0' && !fms->left_adjust && fms->precision == -1)
		fms->padc = '0';
	(*fmt)++;
}
