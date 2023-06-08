/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:52:56 by socana-b          #+#    #+#             */
/*   Updated: 2021/10/02 17:52:57 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*aux1;
	unsigned const char	*aux2;
	unsigned int		i;

	i = 0;
	aux1 = s1;
	aux2 = s2;
	while (i < n)
	{
		if ((aux1[i] > aux2[i]) || (aux1[i] < aux2[i]))
			return (aux1[i] - aux2[i]);
		i++;
	}
	return (0);
}
