/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:13:08 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/07 19:01:53 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	fill_token(char *token, char *str, unsigned int size,
	enum e_state *state)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (str[i] && j < size)
	{
		if (is_true_char(str[i], *state))
			token[j++] = str[i++];
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if ((str[i] == (char)SINGLE_QUOTE && *state == SINGLE_QUOTE)
				|| (str[i] == (char)DOUBLE_QUOTE && *state == DOUBLE_QUOTE))
				*state = NORMAL;
			else if (str[i] == (char)SINGLE_QUOTE && *state == NORMAL)
				*state = SINGLE_QUOTE;
			else if (str[i] == (char)DOUBLE_QUOTE && *state == NORMAL)
				*state = DOUBLE_QUOTE;
			i++;
		}
	}
	token[j] = '\0';
}

/**
 * Creates a new token from str with the given size
 * INPUT:	char *str, unsigned int size
 * OUTPUT:	t_token *	:	NULL	Something failed
 * 							!NULL	Token allocation is correct
 * 							
 */
t_token	*new_token(char *str, unsigned int size, enum e_state state)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (mini_error(NULL, ALLOC_ERR));
	new_token->token = malloc(sizeof(char) * (size + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (mini_error(NULL, ALLOC_ERR));
	}
	fill_token(new_token->token, str, size, &state);
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
void	delete_token_list(t_token_list **list, int full_delete)
{
	t_token	*aux;

	if (!list)
		return ;
	aux = (*list)->start;
	while ((*list)->start)
	{
		(*list)->start = aux->next;
		if (full_delete)
			free(aux->token);
		free(aux);
		aux = (*list)->start;
	}
	free(*list);
	*list = NULL;
}

// TODO: DELETE
#include <stdio.h>
void	print_list(t_token_list *list)
{
	t_token	*aux;
	int		i;

	i = 1;
	if (!list)
		return ;
	aux = list->start;
	while (aux)
	{
		printf("Token %d: token = %s\n", i, aux->token);
		i++;
		aux = aux->next;
	}
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
		return (mini_error(NULL, ALLOC_ERR));
	list->start = NULL;
	list->end = NULL;
	return (list);
}
