/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:13:08 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/05 19:54:39 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Creates a new token from str with the given size
 * INPUT:	char *str, unsigned int size
 * OUTPUT:	t_token *	:	NULL	Something failed
 * 							!NULL	Token allocation is correct
 * 							
 */
t_token	*new_token(char *str, unsigned int size)
{
	t_token			*new_token;
	unsigned int	i;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	new_token->token = malloc(sizeof(char) * (size + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	}
	i = 0;
	while (str[i] && i < size)
	{
		new_token->token[i] = str[i];
		i++;
	}
	new_token->token[i] = '\0';
	new_token->next = NULL;
	return (new_token);
}

/**
 * Creates a new lnode and establishes its value to mvnt and its
 * pointers
 * INPUT:	t_token_list *list, t_token *token
 * OUTPUT:	int	:	0	Failed
 * 					1	Fullfilled
 */
t_token	*add_to_token_list(t_token_list *list, t_token *token)
{
	if (!token)
		return (NULL);
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
	return (token);
}

/**
 * Deletes a list
 * INPUT:	t_token_list *list
 * OUTPUT:	void
 */
void	*delete_token_list(t_token_list **list)
{
	t_token	*aux;

	if (!list || !*list)
		return (NULL);
	aux = (*list)->start;
	while ((*list)->start)
	{
		(*list)->start = aux->next;
		if (aux->token)
			free(aux->token);
		free(aux);
		aux = (*list)->start;
	}
	free(*list);
	*list = NULL;
	return (NULL);
}

/**
 * Creates an empty list with its values initialized to NULL
 * INPUT:	void
 * OUTPUT:	t_token_list *
 */
t_token_list	*create_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	list->start = NULL;
	list->end = NULL;
	return (list);
}
