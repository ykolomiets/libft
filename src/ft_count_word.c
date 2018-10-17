/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:42:11 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/01 19:58:26 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char const *s, char delimetr)
{
	int in_word;
	int	res;

	if (!s)
		return (0);
	res = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == delimetr)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			res++;
		}
		s++;
	}
	return (res);
}
