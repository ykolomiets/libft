/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:38:12 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:40:31 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAGON4_H
# define DRAGON4_H

# include <stdint.h>
# include <stddef.h>
# include "big_int.h"

typedef	int			t_boolean;

typedef enum		e_cutoff_mode
{
	CUTOFF_MODE_UNIQUE,
	CUTOFF_MODE_TOTAL_LENGTH,
	CUTOFF_MODE_FRACTIONAL_LENGTH
}					t_cutoff_mode;

typedef struct		s_dragon4_arg
{
	uint64_t		mantissa;
	int32_t			exponent;
	uint32_t		mantissa_high_bit_idx;
	t_boolean		has_unequal_margins;
	t_cutoff_mode	cutoff_mode;
	uint32_t		cutoff_number;
	char			*out_buffer;
	uint32_t		buffer_size;
	int32_t			*out_exponent;
}					t_dragon4_arg;

typedef struct		s_dragon4_sup
{
	t_big_int		scale;
	t_big_int		scaled_value;
	t_big_int		scaled_margin_low;
	t_big_int		*p_scaled_margin_high;
	t_big_int		optional_margin_high;
	t_boolean		low;
	t_boolean		high;
	int32_t			digit_exponent;
	int32_t			cutoff_exponent;
}					t_dragon4_sup;

typedef enum		e_float_format
{
	PRINT_FLOAT_FORMAT_POSITIONAL,
	PRINT_FLOAT_FORMAT_SCIENTIFIC
}					t_float_format;

typedef struct		s_print_float64_arg
{
	char			*out_buffer;
	uint32_t		buffer_size;
	double			value;
	t_float_format	format;
	t_boolean		is_upper_case;
	int32_t			precision;
}					t_print_float64_arg;

typedef struct		s_format_arg
{
	char			*out_buffer;
	uint32_t		buffer_size;
	uint64_t		mantissa;
	int32_t			exponent;
	uint32_t		mantissa_high_bit_idx;
	t_boolean		has_unequal_margins;
	t_boolean		is_upper_case;
	int32_t			precision;
}					t_format_arg;

void				dragon4_set_start_value(t_dragon4_sup *sup,
						t_dragon4_arg *arg);
void				dragon4_apply_rounding(t_dragon4_sup *sup,
						t_dragon4_arg *arg, uint32_t last_digit,
						char **cur_digit);
uint32_t			dragon4(t_dragon4_arg arg);
uint32_t			log_base_2_uint32(uint32_t val);
uint32_t			log_base_2_uint64(uint64_t val);

uint32_t			format_positional(t_format_arg arg);
uint32_t			format_scientific(t_format_arg arg);

uint32_t			print_inf_nan
(
					char *buffer,
					uint32_t buffer_size,
					uint64_t mantissa,
					t_boolean is_upper_case
);

uint32_t			print_float64(t_print_float64_arg arg);

#endif
