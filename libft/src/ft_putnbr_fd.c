/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:17:56 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/30 10:17:57 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int n)
{
	int	r;

	r = 1;
	while (((n / r) > 9) || ((n / r) < 1))
		r = r * 10;
	return (r);
}

static void	print(int n, int fd)
{
	int	l;

	l = len(n);
	while (l != 0)
	{
		ft_putchar_fd((n / l) + 48, fd);
		n = n - ((n / l) * l);
		l /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		print(n, fd);
	}		
	else
		print(n, fd);
}
