/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float_part2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:50:31 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 20:50:32 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_core.h"
#include "libft.h"

static int	add_point_in_positional(char *buf)
{
	int	i;
	int len;

	len = ft_strlen(buf);
	i = -1;
	while (++i < len)
		if (buf[i] == '.')
			return (0);
	buf[len] = '.';
	buf[len + 1] = '\0';
	return (1);
}

static int	add_point_in_scientific(char *buf)
{
	int	i;
	int len;

	len = ft_strlen(buf);
	i = -1;
	while (++i < len)
	{
		if (buf[i] == '.')
			return (0);
		if (buf[i] == 'e' || buf[i] == 'E')
			break ;
	}
	ft_memmove(buf + i + 1, buf + i, len - i + 1);
	buf[i] = '.';
	return (1);
}

int			insert_point(t_fms *fms, char *buf)
{
	if (fms->altfmt)
	{
		if (fms->specifier == 'f' || fms->specifier == 'F')
			return (add_point_in_positional(buf));
		else
			return (add_point_in_scientific(buf));
	}
	return (0);
}
