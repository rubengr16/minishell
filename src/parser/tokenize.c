/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/04/16 19:09:47 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	changeStatus(char position, int state) // Comprueba si esta en comillas simples dobles o ningunas
{
	if (position == '\'' && state == NORMAL)
			state = SIMPLE_QUOTES;
	else if (position == '\'' && state == SIMPLE_QUOTES)
			state = NORMAL;	
	if (position == '\"' && state == NORMAL)
			state = DOUBLE_QUOTES;
	else if (position == '\"' && state == DOUBLE_QUOTES)
			state = NORMAL;
}

int tokenize(char *line)
{
	unsigned int	scan;	//Variable para iterar la linea
	int				state;	

	scan = 0;
	state = NORMAL;
	while (line[scan])	// Recorremos la linea
	{
		changeStatus(line[scan], &state);
		scan++;
	}
}
