/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:21:41 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:22:39 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	power(int a, int b)
{
	int	c;
	int	i;

	c = a;
	i = 0;
	if (b == 0)
		return (1);
	while (i < b - 1)
	{
		a *= c;
		i++;
	}
	return (a);
}

static char	*str_creator(char *str, long int n, int i, int dlina)
{
	int	j;

	j = 0;
	while (j < dlina)
	{
		str[i++] = '0' + n / power(10, dlina - j - 1);
		n %= power(10, dlina - j - 1);
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int			dlina;
	int long	a;

	dlina = ft_intlen(n);
	i = 0;
	a = n;
	str = (char *)malloc(dlina + 2);
	if (!str)
		return (NULL);
	if (!n)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	if (a < 0)
	{
		str[0] = '-';
		a *= -1;
		i++;
	}
	return (str_creator(str, a, i, dlina));
}
