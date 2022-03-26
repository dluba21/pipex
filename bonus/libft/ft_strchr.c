/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:24:35 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:24:35 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int sym)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)sym)
			return ((char *)&str[i]);
		i++;
	}
	if (sym == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
