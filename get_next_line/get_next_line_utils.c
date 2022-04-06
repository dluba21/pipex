/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 18:45:22 by dluba             #+#    #+#             */
/*   Updated: 2021/12/05 18:58:03 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (-1);
	while (c[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(ft_strlen_gnl(str) + 1);
	if (ptr == NULL)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_gnl(char *s1, char *s2, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_strdup_gnl("");
	i = 0;
	j = 0;
	str = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 2);
	if (str == NULL)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != c)
		str[i++] = s2[j++];
	str[i] = c;
	str[++i] = 0;
	free(s1);
	return (str);
}

int	ft_strchr_gnl(const char *str, int sym)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)sym)
			return (i);
		i++;
	}
	return (i);
}

char	*re_string(char *str, int flag)
{
	char	*temp;
	int		i;

	i = ft_strchr_gnl(str, '\n') + 1;
	str += i;
	temp = ft_strdup_gnl(str);
	str -= i;
	if (flag)
		free(str);
	return (temp);
}
