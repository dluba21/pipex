/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:24:27 by dluba             #+#    #+#             */
/*   Updated: 2021/10/17 14:24:27 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen1(int n)
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

static int	power1(int a, int b)
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

static int	kostyl_checker(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (0);
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return (0);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		return (n);
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		dlina;
	int		j;
	char	c;

	c = 0;
	j = 0;
	dlina = ft_intlen1(n);
	n = kostyl_checker(n, fd);
	if (!n)
		return ;
	while (j < dlina)
	{
		c = '0' + n / power1(10, dlina - j - 1);
		write(fd, &c, 1);
		n %= power1(10, dlina - j - 1);
		j++;
	}
}
