/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:25:06 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:25:06 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*blank_kostyl(void)
{
	char	*s1;

	s1 = malloc(sizeof(char));
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (blank_kostyl());
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	if (start < ft_strlen(s) || (len + start) <= ft_strlen(s))
	{
		while (i < len)
			s1[i++] = s[start++];
	}
	s1[i] = '\0';
	return (s1);
}
