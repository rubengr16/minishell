/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinsep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:05:55 by rgallego          #+#    #+#             */
/*   Updated: 2022/09/21 22:06:15 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinsep(char const *s1, char const *s2, char *c)
{
	int		len;
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	s = malloc(sizeof(char) * (len));
	if (!s)
		return (NULL);
	(void)ft_strlcpy(s, s1, len);
	(void)ft_strlcat(s, c, len);
	(void)ft_strlcat(s, s2, len);
	return (s);
}
