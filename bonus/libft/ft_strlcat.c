/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:34:49 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:34:49 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *buf, const char *src, size_t n)
{
	size_t	i;
	size_t	len_buf;
	size_t	len_src;

	len_buf = ft_strlen(buf);
	len_src = ft_strlen(src);
	i = 0;
	while (src[i] && (i + len_buf + 1) < n)
	{
		buf[i + len_buf] = src[i];
		i++;
	}
	buf[i + len_buf] = '\0';
	if (n <= len_buf)
		return (n + ft_strlen(src));
	return (len_buf + len_src);
}
