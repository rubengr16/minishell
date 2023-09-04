/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 01:31:11 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/04 18:42:37 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	get_state(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (METACHAR);
	else if (c == (char)SINGLE_QUOTE)
		return (SINGLE_QUOTE);
	else if (c == (char)DOUBLE_QUOTE)
		return (DOUBLE_QUOTE);
	else if (ft_strchr(" \t\n\v\f\r", c))
		return (SPACE_CHAR);
	else
		return (NORMAL);
}

int	is_end_of_token(char c, enum e_state state)
{
	return (c && (state != NORMAL
			|| (!ft_strchr(" \t\n\v\f\r", c)
				&& get_state(c) != METACHAR)));
}

int	is_end_of_vble(char c, enum e_state state)
{
	return (c && (!ft_strchr(" \t\n\v\f\r", c))
		&& c != (char)DOUBLE_QUOTE && c != '$' && (state == DOUBLE_QUOTE
			|| (get_state(c) != METACHAR && c != (char)SINGLE_QUOTE)));
}

int	is_true_quote(char c, enum e_state state)
{
	return ((state == NORMAL
			&& (c == (char)SINGLE_QUOTE || c == (char)DOUBLE_QUOTE))
		|| (state == SINGLE_QUOTE && c == (char)SINGLE_QUOTE)
		|| (state == DOUBLE_QUOTE && c == (char)DOUBLE_QUOTE));
}

int	is_true_char(char c, enum e_state state)
{
	return ((c != (char)SINGLE_QUOTE && c != (char)DOUBLE_QUOTE)
		|| (state == SINGLE_QUOTE && c == (char)DOUBLE_QUOTE)
		|| (state == DOUBLE_QUOTE && c == (char)SINGLE_QUOTE));
}
