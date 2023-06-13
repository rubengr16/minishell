/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:23:27 by socana-b          #+#    #+#             */
/*   Updated: 2021/10/05 16:23:28 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char const		*auxsrc;
	char			*auxdst;

	auxsrc = src;
	auxdst = dst;
	if (dst > src)
	{
		i = len;
		while (i--)
			auxdst[i] = auxsrc[i];
	}
	else if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			auxdst[i] = auxsrc[i];
			i++;
		}
	}
	return (dst);
}
