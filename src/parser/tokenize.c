/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/16 01:13:07 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void changeStatus(char position, int *state, int *n_position) // Comprueba si esta en comillas simples dobles o ningunas
{
	if (position == '\'' && *state == NORMAL)
		*state = SINGLE_QUOTES;
	else if (position == '\'' && *state == SINGLE_QUOTES)
		*state = NORMAL;	
	if (position == '\"' && *state == NORMAL)
		*state = DOUBLE_QUOTES;
	else if (position == '\"' && *state == DOUBLE_QUOTES)
		*state = NORMAL;
	if (position == '\"' || position == '\'')
		*n_position = *n_position + 1;
}

/*
unsigned int	getToken(char *line, unsigned int length, int *state)
{
	unsigned int	position;

	position = length;
	while (line[position] != ' ' || *state == NORMAL)
	{
		changeStatus(line[position], state, &position)
		position++;
	}
	return (position);
}
*/

unsigned int	is_metacharacter(int i, char *line)
{
	if (0 < i && line[i - 1] == '\\')
		return (NORMAL);
	else if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		return (METACHARACTER);
	else if (line[i] == '\'')
		return (SINGLE_QUOTES);
	else if (line[i] == '\"')
		return (DOUBLE_QUOTES);
	else
		return (NORMAL);
}

t_token_list *tokenize(char *line)
{
	t_token_list *list;
	t_token *token;
	unsigned int	i;	//Variable para iterar la linea
	unsigned int	start; // Variable startiliar para calcular el tamaño de las variables
	enum e_state	state;

	i = 0;
	list = create_list();
	if (!list)
		return (NULL);
	while (line[i])	// Recorremos la linea
	{
		while (line[i] == ' ')
			i++;
		//NOTE (Ruben): DEPRECATED?: changeStatus(line[i], &state, &i); // Cambiamos el estado cada
		start = i;
		state = is_metacharacter(i, line);
		if (state != METACHARACTER)
			while (line[i] && line[i] != (char)state)
				i++;
		token = new_token(&line[start], start - i, state);
		if(add_to_list(list, token))
		{
			delete_list(list);
			return(NULL);
		}
	}
	return (list);
}
