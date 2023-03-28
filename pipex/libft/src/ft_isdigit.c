/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 13:11:27 by rgallego          #+#    #+#             */
/*   Updated: 2022/02/23 20:28:36 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function which receives a character and decides if it is a digit
 * INPUT:	int c
 * OUTPUT:	int
 */
int	ft_isdigit(int c)
{
	int	digit;

	digit = 0;
	if ('0' <= c && c <= '9')
		digit = 1;
	return (digit);
}
