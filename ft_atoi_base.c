/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 20:12:02 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 20:17:07 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_base(char const *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (-1);
		j = i + 1;
		while (base[j])
			if (base[j] == base[i])
				return (-1);
			else
				j++;
		i++;
	}
	return (i);
}

static int	ft_check_sign(char **str)
{
	if (**str == '+')
		(*str)++;
	else if (**str == '-' && (*str)++)
		return (-1);
	return (1);
}

static int	ft_check_str(char const *str, char const *base, int base_size)
{
	int base_count;

	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			str++;
			continue ;
		}
		base_count = 0;
		while (base_count < base_size)
		{
			if (*str == base[base_count])
				break ;
			base_count++;
		}
		if (base_count == base_size)
			return (1);
		str++;
	}
	return (0);
}

int			ft_atoi_base(char const *str, char const *base)
{
	int result;
	int	base_size;
	int sign;
	int	i;

	base_size = ft_check_base(base);
	if (!*str || base_size <= 1 || ft_check_str(str, base, base_size))
		return (0);
	sign = ft_check_sign((char**)&str);
	result = 0;
	while (*str)
	{
		i = -1;
		while (++i < base_size)
			if (*str == base[i])
			{
				result = result * base_size + i;
				break ;
			}
			else if (*str == '+' || *str == '-')
				return (result * sign);
		str++;
	}
	return (result * sign);
}
