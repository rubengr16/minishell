/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:40:38 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/30 12:40:39 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char				*aux;
	unsigned int		i;

	i = 0;
	aux = malloc(size * count);
	if (aux == NULL)
		return (NULL);
	while (i < count * size)
	{
		aux[i] = '\0';
		i++;
	}
	return (aux);
}
