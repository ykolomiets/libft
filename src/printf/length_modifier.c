/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 21:05:24 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 21:05:26 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

int			is_length_modifier_start(char c)
{
	if (c == 'h' || c == 'l' || c == 'z' || c == 'j')
		return (1);
	return (0);
}

void		set_length_modifier(t_fms *fms, t_length_modifier modifier)
{
	if (fms->length_modifier < modifier)
		fms->length_modifier = modifier;
}

void		parse_length_modifier(const char **fmt, t_fms *fms)
{
	if (**fmt == 'h')
	{
		if (*(*fmt + 1) == 'h')
		{
			(*fmt)++;
			set_length_modifier(fms, LM_SHORT_SHORT);
		}
		else
			set_length_modifier(fms, LM_SHORT);
	}
	else if (**fmt == 'l')
	{
		if (*(*fmt + 1) == 'l')
		{
			(*fmt)++;
			set_length_modifier(fms, LM_LONG_LONG);
		}
		else
			set_length_modifier(fms, LM_LONG);
	}
	else if (**fmt == 'z')
		set_length_modifier(fms, LM_Z);
	else if (**fmt == 'j')
		set_length_modifier(fms, LM_J);
	(*fmt)++;
}
