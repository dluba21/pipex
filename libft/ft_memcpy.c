/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:24:02 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:25:37 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_0, const void *src_0, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;

	dest = dest_0;
	src = src_0;
	if (!src && !dest)
		return (NULL);
	while (n--)
		dest[n] = src[n];
	return (dest);
}
