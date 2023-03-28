/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:26:28 by rgallego          #+#    #+#             */
/*   Updated: 2022/01/29 16:05:16 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function which receives a string with a number writen in ASCII and returns
 * the integer representation of it.
 * INPUT:	const char *s, const char *base, int base_len
 * OUTPUT:	int
 */
int	ft_atoi_base(const char *s, const char *base, int base_len)
{
	int					sign;
	unsigned long long	num;
	char				*ptr;

	sign = 1;
	num = 0;
	while (*s && (*s == '\t' || *s == '\n' || *s == '\v' || *s == '\f'
			|| *s == '\r' || *s == ' '))
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	ptr = ft_strchr(base, *s);
	while (*s && ptr)
	{
		num = num * base_len + (ptr - base);
		s++;
		ptr = ft_strchr(base, *s);
	}
	if (sign == 1 && num > LLONG_MAX)
		return (-1);
	if (sign == -1 && num > LLONG_MAX)
		return (0);
	return (sign * num);
}
