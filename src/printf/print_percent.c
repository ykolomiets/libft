/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:09:59 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 20:10:28 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"

int		print_percent(t_printf *options, t_fms *fms)
{
	int	print_res;

	fms->length--;
	if (!fms->left_adjust)
		while (--fms->length >= 0)
			if ((print_res = options->putc(options, fms->padc)))
				return (print_res);
	if ((print_res = options->putc(options, '%')))
		return (print_res);
	print_left_adjust(options, fms);
	return (0);
}
