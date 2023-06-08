/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:22:47 by socana-b          #+#    #+#             */
/*   Updated: 2021/10/05 16:22:48 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	char const		*auxsrc;
	char			*auxdst;

	if ((dst == NULL) && (src == NULL))
		return (NULL);
	i = 0;
	auxsrc = src;
	auxdst = dst;
	while (i < n)
	{
		auxdst[i] = auxsrc[i];
		i++;
	}
	return (dst);
}
