/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:00:14 by rgallego          #+#    #+#             */
/*   Updated: 2022/08/29 20:54:12 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function which decides if a string is only numerical
 * INPUT:	char *str
 * OUTPUT:	int	:	1	numerical
 *					0	non numerical
 */
int	ft_strisnumber(char *str)
{
	int	cnt;

	if (!str)
		return (0);
	cnt = 0;
	if (str[cnt] == '-')
		cnt++;
	while (str[cnt] && ft_isdigit(str[cnt]))
		cnt++;
	if (!str[cnt])
		return (1);
	else
		return (0);
}
