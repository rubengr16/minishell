/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:44:00 by rgallego          #+#    #+#             */
/*   Updated: 2022/08/29 20:58:26 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_check(int nb, char *str)
{
	if ((!nb || nb == -1) && (ft_strlen(str) > 2))
		return (1);
	else
		return (0);
}
