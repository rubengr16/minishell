/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/21 20:40:41 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

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

void	manage_quotes(enum e_state *state, unsigned int *i, char c)
{
	(*i)++;
	if (*state != NORMAL)
		*state = NORMAL;
	else if (c == (char)SINGLE_QUOTES)
		*state = SINGLE_QUOTES;
	else if (c == (char)DOUBLE_QUOTES)
		*state = DOUBLE_QUOTES;
}

t_token	*get_token(char *line, unsigned int *i, enum e_state state)
{
	unsigned int	start;

	start = *i;
	if (state != NORMAL)
		start = ++(*i);
	while (line[*i] && (state != NORMAL || (get_state(line[*i]) != SPACE_CHAR
		&& get_state(line[*i]) != METACHAR)))
	{
		if (line[*i] == '$' && state != SINGLE_QUOTES
			&& !expand(&line, i,  state))
				return (NULL);
		else if (state == NORMAL && (line[*i] == '\'' || line[*i] =='\"'))
			manage_quotes(&state, i, line[*i]);
		else
			(*i)++;
	}
	if (state != NORMAL)
		return (NULL);
	return (new_token(&line[start], (unsigned int)(*i - start)));
}

t_token_list	*tokenize(char *line)
{
	t_token_list	*list;
	t_token			*token;
	unsigned int	i;
	enum e_state	state;

	i = 0;
	list = create_list();
	if (!list)
		return (NULL);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		state = get_state(line[i]);
		if (state != METACHAR)
			token = get_token(line, &i, state);
		else
			token = new_token(&line[i++], 1);
		if (!add_to_list(list, token))
		{
			delete_list(list);
			return (NULL);
		}
	}
	return (list);
}
