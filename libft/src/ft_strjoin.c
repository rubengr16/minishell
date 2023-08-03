/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:41:27 by socana-b          #+#    #+#             */
/*   Updated: 2023/08/03 17:57:33 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aux;
	int		i;
	int		j;

	j = 0;
	i = 0;
	aux = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		aux[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		aux[i] = s2[j];
		j++;
		i++;
	}
	aux[i] = '\0';
	return (aux);
}
