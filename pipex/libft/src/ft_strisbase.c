/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:02:16 by rgallego          #+#    #+#             */
/*   Updated: 2022/02/23 20:31:15 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisbase(char *str, char *base)
{
	int	cnt;

	if (!str || !base)
		return (0);
	cnt = 0;
	while (str[cnt] && ft_strchr(base, str[cnt]))
		cnt++;
	if (!str[cnt])
		return (1);
	else
		return (0);
}	
