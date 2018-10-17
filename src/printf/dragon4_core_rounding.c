/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_core_rounding.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 15:35:49 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/06 15:35:50 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dragon4.h"

static t_boolean	is_round_down(t_dragon4_sup *sup, uint32_t last_digit)
{
	t_boolean	round_down;
	int32_t		compare;

	round_down = sup->low;
	if (sup->low == sup->high)
	{
		bi_mult_bi_by_2_inplace(&sup->scaled_value);
		compare = bi_compare(&sup->scaled_value, &sup->scale);
		round_down = compare < 0;
		if (compare == 0)
			round_down = (last_digit & 1) == 0;
	}
	return (round_down);
}

static void			round_up
(
	t_dragon4_arg *arg,
	char **cur_digit,
	uint32_t last_digit
)
{
	if (last_digit == 9)
		while (1)
		{
			if (*cur_digit == arg->out_buffer)
			{
				**cur_digit = '1';
				(*cur_digit)++;
				*arg->out_exponent = 1;
				break ;
			}
			--(*cur_digit);
			if (**cur_digit != '9')
			{
				**cur_digit += 1;
				(*cur_digit)++;
				break ;
			}
		}
	else
	{
		**cur_digit = (char)('0' + last_digit + 1);
		(*cur_digit)++;
	}
}

void				dragon4_apply_rounding
(
		t_dragon4_sup *sup,
		t_dragon4_arg *arg,
		uint32_t last_digit,
		char **cur_digit
)
{
	t_boolean	round_down;

	round_down = is_round_down(sup, last_digit);
	if (round_down)
	{
		**cur_digit = (char)('0' + last_digit);
		(*cur_digit)++;
	}
	else
		round_up(arg, cur_digit, last_digit);
}
