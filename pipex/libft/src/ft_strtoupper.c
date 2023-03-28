/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:49:20 by rgallego          #+#    #+#             */
/*   Updated: 2022/08/29 20:50:05 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	int		i;
	char	*strlower;

	i = 0;
	strlower = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		strlower[i] = ft_tolower(str[i]);
		i++;
	}
	strlower[i] = str[i];
	return (strlower);
}
