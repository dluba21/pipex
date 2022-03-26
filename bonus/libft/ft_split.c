/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:24:31 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:24:31 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_counter(char const *str, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	j;

	j = 0;
	i = 0;
	while (i < ft_strlen(str))
	{
		start = i;
		while (i < ft_strlen(str) && str[i] != c && str[i] != '\t')
			i++;
		end = i;
		if (end - start > 0)
			j++;
		i++;
	}
	return (j);
}

static char	**anti_leak(char **big, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(big[i++]);
	free(big);
	return (NULL);
}

static char	**big_str_creator(char const *s, char c, char **big)
{
	size_t	start;
	size_t	end;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		start = i;
		while (i < ft_strlen(s) && s[i] != c && s[i] != '\t')
			i++;
		end = i;
		if (end - start > 0)
		{
			big[j] = ft_substr(s, start, end - start);
			if (!big[j])
				return (anti_leak(big, j));
			j++;
		}
		i++;
	}
	big[j] = NULL;
	return (big);
}

char	**ft_split(char const *s, char c)
{
	char	**big;

	if (!s)
		return (NULL);
	big = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (big == NULL)
		return (NULL);
	return (big_str_creator(s, c, big));
}
