/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/15 00:35:51 by rgallego         ###   ########.fr       */
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
t_token_list *tokenize(char *line)
{
	t_token_list *list;
	t_token *token;
	unsigned int	i;	//Variable para iterar la linea
	unsigned int	aux; // Variable auxiliar para calcular el tamaño de las variables
	enum e_state	state;

	i = 0;
	aux = 0;
	state = NORMAL;
	list = create_list();
	while (line[i])	// Recorremos la linea
	{
		if (line[i] == ' ' && state == NORMAL) // omitimos espacios
		{
			i++;
			continue; //Esto esta permitido?
		}
		//changeStatus(line[i], &state, &i); // Cambiamos el estado cada
		aux = i;
		while (line[aux] != ' ' && line[aux])
			aux++;
		token = new_token(line + i, (aux - i) + 1);
		if(add_to_list(list, token))
		{
			delete_list(list);
			return(NULL);
		}
		i = aux;
	}
	return (list);
}
