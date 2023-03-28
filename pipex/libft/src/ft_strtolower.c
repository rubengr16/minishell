/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:49:20 by rgallego          #+#    #+#             */
/*   Updated: 2022/08/29 20:50:18 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *str)
{
	int		i;
	char	*strupper;

	i = 0;
	strupper = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		strupper[i] = ft_toupper(str[i]);
		i++;
	}
	strupper[i] = str[i];
	return (strupper);
}
