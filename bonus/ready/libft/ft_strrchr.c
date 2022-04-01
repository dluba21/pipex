/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:32:58 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:32:58 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int sym)
{
	char	*p;

	p = NULL;
	if (!sym)
		return ((char *)&str[ft_strlen(str)]);
	while (*str)
	{
		if (*str == (unsigned char)sym)
			p = (char *)str;
		str++;
	}
	return (p);
}
