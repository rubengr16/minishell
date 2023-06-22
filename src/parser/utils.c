/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:31:11 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/23 01:31:34 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	get_state(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (METACHAR);
	else if (c == '\'')
		return (SINGLE_QUOTES);
	else if (c == '\"')
		return (DOUBLE_QUOTES);
	else if (c == ' ')
		return (SPACE_CHAR);
	else
		return (NORMAL);
}

void	manage_quotes(enum e_state *state, unsigned int *i,
	unsigned int *adjust_size, char c)
{
	(*i)++;
	(*adjust_size)++;
	if (*state != NORMAL)
		*state = NORMAL;
	else if (c == (char)SINGLE_QUOTES)
		*state = SINGLE_QUOTES;
	else if (c == (char)DOUBLE_QUOTES)
		*state = DOUBLE_QUOTES;
}
