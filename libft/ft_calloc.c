/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:16:28 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:22:12 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elem, size_t size)
{
	void			*ptr;
	unsigned char	*ptr1;
	size_t			i;

	i = 0;
	ptr = (void *)malloc(elem * size);
	ptr1 = ptr;
	if (ptr == NULL)
		return (NULL);
	while (i < elem * size)
	{
		ptr1[i] = 0;
		i++;
	}
	return (&ptr[0]);
}
