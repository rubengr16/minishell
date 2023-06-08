/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:13:08 by rgallego          #+#    #+#             */
/*   Updated: 2023/04/16 19:16:24 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_token	*new_token(char *str, unsigned int length)
{
	t_token			*new_token;
	unsigned int	i;

	i = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = malloc(sizeof(char) * length);
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	while (i < length)
	{
		new_token->token[i] = str[i];
		i++;
	}
	new_token->token[i] = '\0';
	new_token->next = NULL;
	return (new_token);
}

int	add_to_list(t_list *list, t_token *token) // Si todo funciona devuelve 0, si no 1
{
	if (token)
	{
		if (!list->start)
		{
			list->start = token;
			list->end = token;
		}
		else
		{
			list->end->next = token;
			list->end = token;
		}
		return (0);
	}
	else
		write(2, "minishell: Allocation failed\n", 29);
	return (1);
}

void	delete_list(t_list *list)
{
	t_token	*aux;

	while(aux)
	{
		aux = aux->next;
		free(list->start->token);
		free(list->start);
		list->start = aux;
	}
}

void	print_list(t_list *list)
{
	t_token	*aux;
	int		i = 1;

	aux = list->start;
	while (aux)
	{
		printf("Token %d: %s\n", i, aux->token);
		i++;
		aux = aux->next;
	}
}

t_list	*create_list()
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->start = NULL;
}
