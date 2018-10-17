/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:41:01 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:47:45 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_CORE_H
# define PRINTF_CORE_H

# include <stdarg.h>
# include <inttypes.h>

# define BUF_SIZE 512
# define INT_BUF_SIZE sizeof(intmax_t) * 8

# define CHAR_TO_DIGIT(x) ((x) - '0')

# define TRUE 1
# define FALSE 0

typedef int				t_boolean;

typedef	enum			e_length_modifier
{
	LM_NONE,
	LM_SHORT_SHORT,
	LM_SHORT,
	LM_LONG,
	LM_LONG_LONG,
	LM_J,
	LM_Z
}						t_length_modifier;

typedef enum			e_specifier_type
{
	ST_NONE,
	ST_NULL_TERNINATOR,
	ST_PERCENT,
	ST_INTEGER,
	ST_CHARACTER,
	ST_STRING,
	ST_FLOAT,
	ST_POINTER,
}						t_specifier_type;

typedef struct			s_printf
{
	int					fd;
	va_list				*ap;
	char				buffer[BUF_SIZE];
	int					pos_in_buffer;
	char				*external_buffer;
	int					external_buffer_size;
	int					(*putc)(struct s_printf *, char);
	int					(*flush)(struct s_printf *);
	int					printed;
}						t_printf;

typedef struct			s_fms
{
	char				specifier;
	t_specifier_type	specifier_type;
	t_boolean			left_adjust;
	t_boolean			altfmt;
	char				plus_sign;
	char				padc;
	t_length_modifier	length_modifier;
	int					length;
	int					precision;
}						t_fms;

typedef struct			s_int_options
{
	int					base;
	int					capitals;
	t_boolean			is_signed;
	char				sign_char;
}						t_int_options;

int						printf_core(t_printf *options, const char *fmt);
int						is_flag(char c);
void					parse_flag(const char **fmt, t_fms *fms);
int						is_length_start(char c);
void					parse_length(const char **fmt, t_fms *fms,
										va_list *ap);
int						is_precision_start(char c);
void					parse_precision(const char **fmt, t_fms *fms,
										va_list *ap);
int						is_length_modifier_start(char c);
void					set_length_modifier(t_fms *fms,
											t_length_modifier modifier);
void					parse_length_modifier(const char **fmt, t_fms *fms);
int						is_specifier(char c);
void					parse_specifier(const char **fmt, t_fms *fms);
int						print_percent(t_printf *options, t_fms *fms);
int						print_char(t_printf *options, t_fms *fms);
int						uintmax_to_buf(uintmax_t u, int base,
							int capitals, char **buf);
char					*get_prefix_for_int(uintmax_t u, t_fms *fms,
							int base, int capitals);
int						print_num(uintmax_t u, t_printf *options,
									t_fms *fms, t_int_options *int_opt);
int						print_integer(t_printf *options, t_fms *fms);
int						print_float(t_printf *options, t_fms *fms);
int						insert_point(t_fms *fms, char *buf);
int						print_string(t_printf *options, t_fms *fms);
int						print_pointer(t_printf *options, t_fms *fms);
int						print_none_specifier(t_printf *options, t_fms *fms);
int						print_left_adjust(t_printf *options, t_fms *fms);
int						wchar_length_in_bytes(wchar_t ch);
int						wchartobuf(wchar_t ch, char *buf);

#endif
