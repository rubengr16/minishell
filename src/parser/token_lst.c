/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:13:08 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/21 20:30:26 by rgallego         ###   ########.fr       */
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
t_token	*new_token(char *str, unsigned int size, enum e_state state)
{
	t_token			*new_token;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token = malloc(sizeof(char) * (size + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	while (str[i] && j < size)
	{
		if ((str[i] != '\'' && str[i] != '\"')
			|| (state == SINGLE_QUOTES && str[i] == '\"')
			|| (state == DOUBLE_QUOTES && str[i] == '\''))
			new_token->token[j++] = str[i++];
		else if (str[i] == '\'' || str[i] == '\"')
		{
			if ((str[i] == (char)SINGLE_QUOTES && state == SINGLE_QUOTES) || (str[i] == (char)DOUBLE_QUOTES && state == DOUBLE_QUOTES))
				state = NORMAL;
			else if (str[i] == (char)SINGLE_QUOTES && state == NORMAL)
				state = SINGLE_QUOTES;
			else if (str[i] == (char)SINGLE_QUOTES && state == NORMAL)
				state = DOUBLE_QUOTES;
			i++;
		}
	}
	new_token->token[j] = '\0';
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
int	add_to_list(t_token_list *list, t_token *token)
{
	if (!token)
	{
		write(2, "minishell: Allocation failed\n", 29);
		return (0);
	}
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
	return (1);
}

/**
 * Deletes a list
 * INPUT:	t_token_list *list
 * OUTPUT:	void
 */
void	delete_list(t_token_list *list)
{
	t_token	*aux;

	if (!list)
		return ;
	aux = list->start;
	while (list->start)
	{
		aux = aux->next;
		free(list->start->token);
		free(list->start);
		list->start = aux;
	}
}

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
		printf("Token %d: %s\n", i, aux->token);
		i++;
		aux = aux->next;
	}
}

/**
 * Creates an empty list with its values initialized to NULL
 * INPUT:	void
 * OUTPUT:	t_token_list *
 */
t_token_list	*create_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->start = NULL;
	list->end = NULL;
	return (list);
}
