/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:11:12 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/30 10:11:13 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	leng(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	if (n == 0)
		i++;
	while (n >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	reverse(char *str)
{
	unsigned long int	i;
	char				aux;

	i = 0;
	while (i < ft_strlen(str) / 2)
	{
		aux = str[i];
		str[i] = str[ft_strlen(str) - i - 1];
		str[ft_strlen(str) - i - 1] = aux;
		i++;
	}	
}

static int	minus(int n, char *str)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		n = 214748364;
		str[i] = '8';
		i++;
	}
	if (n < 0)
		n *= -1;
	while (n >= 1)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	str[i] = '-';
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		i;

	i = 0;
	num = malloc (sizeof(char) * (leng(n) + 1));
	if (num == NULL)
		return (NULL);
	if (n < 0)
		i = minus(n, num);
	else if (n == 0)
		num[i++] = '0';
	else
	{
		while (n > 0)
		{
			num[i] = (n % 10) + 48;
			n = n / 10;
			i++;
		}
	}
	num[i] = '\0';
	reverse(num);
	return (num);
}
