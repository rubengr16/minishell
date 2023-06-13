/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:41:27 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/18 16:41:29 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux;
	int		i;
	int		j;

	if (!s1 || !s2)
		return ("");
	j = 0;
	i = 0;
	aux = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (NULL);
	while (s1[i])
	{
		aux[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		aux[i] = s2[j];
		j++;
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
