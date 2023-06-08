/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:26:05 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/18 16:26:08 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*auxf(void)
{
	char	*nul;

	nul = malloc (sizeof(char));
	if (!nul)
		return (NULL);
	*nul = '\0';
	return (nul);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*aux;

	if (!s)
		return ("");
	if (start >= ft_strlen(s))
		return (auxf());
	j = 0;
	i = start;
	if ((ft_strlen(s) - start) < len)
		aux = malloc (sizeof(char) * ft_strlen(s) - start + 1);
	else
		aux = malloc (sizeof(char) * len + 1);
	if (aux == NULL)
		return (NULL);
	while ((j < len) && s[i])
	{
		aux[j] = s[i];
		i++;
		j++;
	}
	aux[j] = '\0';
	return (aux);
}
