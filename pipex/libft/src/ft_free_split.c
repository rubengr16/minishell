/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:17:28 by rgallego          #+#    #+#             */
/*   Updated: 2022/03/07 12:48:53 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * function which frees all resources used by the program after executing an 
 * split
 * INPUT:	char **set
 * OUTPUT:	void
 */
void	ft_free_split(char **set)
{
	int	i;

	i = 0;
	if (set)
	{
		while (set[i])
		{
			free(set[i]);
			i++;
		}
		free(set);
	}
}
