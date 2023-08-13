/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:38:33 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/14 01:43:35 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_isstrnbr(char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-' && !ft_isdigit(s[i + 1]))
		return (0);
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	return (1);
}
