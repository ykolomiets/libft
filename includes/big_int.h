/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:28:28 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:50:26 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIG_INT_H
# define BIG_INT_H

# include <stdint.h>

# define BIG_INT_MAX_BLOCK 35

typedef	int		t_boolean;

typedef	struct	s_big_int
{
	uint32_t	length;
	uint32_t	blocks[BIG_INT_MAX_BLOCK];
}				t_big_int;

typedef	struct	s_bi_add_support
{
	t_big_int	*large;
	t_big_int	*small;
	uint32_t	*large_cur;
	uint32_t	*large_end;
	uint32_t	*small_cur;
	uint32_t	*small_end;
}				t_bi_add_support;

typedef	struct	s_bi_div_support
{
	uint64_t	borrow;
	uint64_t	carry;
	uint64_t	product;
	uint64_t	difference;
}				t_bi_div_support;

typedef struct	s_bi_mult_support
{
	t_big_int	*large;
	t_big_int	*small;
	uint32_t	*large_beg;
	uint32_t	*large_end;
	uint32_t	*small_beg;
	uint32_t	*small_end;
}				t_bi_mult_support;

t_boolean		bi_is_zero(t_big_int *big_int);

void			bi_set_u32(t_big_int *big_int, uint32_t val);
void			bi_set_u64(t_big_int *big_int, uint64_t val);
uint32_t		bi_get_u32(t_big_int *big_int);
int				bi_compare(t_big_int *left, t_big_int *right);
void			bi_add(t_big_int *result, t_big_int *left, t_big_int *right);
void			bi_mult_bi_by_bi(t_big_int *result, t_big_int *left,
									t_big_int *right);
void			bi_mult_bi_by_uint32(t_big_int *result, t_big_int *left,
									uint32_t right);
void			bi_mult_bi_by_2(t_big_int *result, t_big_int *in);

void			bi_mult_bi_by_2_inplace(t_big_int *result);
void			bi_mult_bi_by_10_inplace(t_big_int *result);
void			bi_pow10(t_big_int *result, uint32_t exponent);
void			bi_mult_by_pow10(t_big_int *result, t_big_int *in,
									uint32_t exponent);
void			bi_pow2(t_big_int *result, uint32_t exponent);
uint32_t		bi_divide_with_remainder_maxquotient9(t_big_int	*dividend,
														t_big_int *divisor);
void			bi_shift_left(t_big_int *result, uint32_t shift);

uint32_t		get_pow10_uint32(uint32_t pow);
t_big_int		*get_pow10_big_int(uint32_t pow);

#endif
