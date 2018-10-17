/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:05:43 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:05:47 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include "libft.h"

int		is_length_start(char c)
{
	if (IS_DIGIT(c) || c == '*')
		return (1);
	return (0);
}

void	parse_length(const char **fmt, t_fms *fms, va_list *ap)
{
	char	c;

	c = **fmt;
	fms->length = 0;
	if (IS_DIGIT(c))
	{
		while (IS_DIGIT(c))
		{
			fms->length = fms->length * 10 + CHAR_TO_DIGIT(c);
			(*fmt)++;
			c = **fmt;
		}
	}
	else if (c == '*')
	{
		fms->length = va_arg(*ap, int);
		if (fms->length < 0)
		{
			fms->left_adjust = TRUE;
			fms->length = -fms->length;
		}
		(*fmt)++;
	}
}
