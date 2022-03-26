/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:24:16 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:24:16 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest0, const void *src0, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*src;

	dest = (unsigned char *)dest0;
	src = (unsigned char *)src0;
	i = 0;
	if (dest0 == NULL && src0 == NULL)
		return (NULL);
	if (dest > src && dest < (src + n))
	{
		while (n--)
			*(dest + n) = *(src + n);
		return (dest);
	}
	while (i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	return (dest);
}
