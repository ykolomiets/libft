/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:19:57 by ykolomie          #+#    #+#             */
/*   Updated: 2016/12/02 19:48:12 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_create_table(char const *s, char c, int *word_count)
{
	int		in_word;
	char	**table;

	*word_count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			(*word_count)++;
		}
		s++;
	}
	table = (char**)malloc(sizeof(char*) * (*word_count + 1));
	if (!table)
		return (NULL);
	table[*word_count] = 0;
	return (table);
}

static char	*ft_fill_word(char **s, char c)
{
	char	*res;
	int		size;
	int		i;

	while (**s == c)
		(*s)++;
	size = 0;
	while ((*s)[size] != c && (*s)[size] != '\0')
		size++;
	res = (char*)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = '\0';
	i = 0;
	while (i < size)
	{
		res[i++] = **s;
		(*s)++;
	}
	return (res);
}

char		**ft_strsplit(char const *s, char c)
{
	int		word_count;
	int		i;
	char	**res;

	if (!s)
		return (NULL);
	res = ft_create_table(s, c, &word_count);
	if (!res)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		if (!(res[i] = ft_fill_word((char**)&s, c)))
		{
			ft_free_table(&res, i + 1);
			return (NULL);
		}
		i++;
	}
	return (res);
}
