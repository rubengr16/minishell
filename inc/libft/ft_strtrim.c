/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:42:38 by socana-b          #+#    #+#             */
/*   Updated: 2021/09/24 14:42:39 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	full(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	aux;

	aux = 0;
	i = 0;
	j = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (set[j] == s1[i])
				aux++;
			j++;
		}
		if (aux == 0)
			return (0);
		aux = 0;
		i++;
		j = 0;
	}
	return (1);
}

static int	find(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	forge(const char *str, unsigned int start,
	unsigned int end, char *res)
{
	int	i;

	i = 0;
	while (start < ft_strlen(str) - end)
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		i;
	int		k[2];

	if (!s1)
		return ("");
	if (full(s1, set))
	{
		result = malloc (sizeof(char));
		*result = '\0';
		return (result);
	}
	i = -1;
	k[0] = 0;
	k[1] = 0;
	while (find(s1[++i], set))
		k[0]++;
	i = ft_strlen(s1) - 1;
	while (find(s1[i--], set))
		k[1]++;
	result = malloc(sizeof(char) * (ft_strlen(s1) + 1 - k[1] - k[0]));
	if (!result)
		return (NULL);
	forge(s1, k[0], k[1], result);
	return (result);
}
