/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blueflare <blueflare@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 11:14:06 by socana-b          #+#    #+#             */
/*   Updated: 2022/08/04 10:51:53 by blueflare        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmpst(const char *str, const char *find,
unsigned long int i, size_t len)
{
	int	j;
	int	aux;

	j = 0;
	aux = 1;
	if ((find[j] == str[i]) && (i <= (len - 1)))
	{
		while ((aux) && find[j] && (i <= (len - 1)))
		{
			if (find[j] != str[i])
				aux = 0;
			i++;
			j++;
		}
		if (find[j] != '\0')
			aux = 0;
		return (aux);
	}
	else
		return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned long int	i;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while ((i < len) && (str[i]))
	{
		if (cmpst(str, to_find, i, len))
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
