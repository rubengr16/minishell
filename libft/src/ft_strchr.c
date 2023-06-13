/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:19:16 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/14 12:19:18 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find(const char *s, unsigned char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (!c && !s[i])
		return (i);
	return (-1);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	aux;

	aux = (unsigned char)c;
	if (find(s, aux) >= 0)
		return ((char *)(s + find(s, aux)));
	else
		return (0);
}
