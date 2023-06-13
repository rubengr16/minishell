/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:56:39 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/28 14:56:41 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, unsigned long int len)
{
	unsigned int	i;
	char			*baux;

	baux = b;
	i = 0;
	while (i < len)
	{
		baux[i] = c;
		i++;
	}
	return (b);
}
