/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/20 23:50:09 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>

unsigned int	is_metachar(char c)
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

void	manage_quotes(enum e_state *state, int *adjust_size, char c)
{
	(*adjust_size)++;
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
	int				adjust_size;
	t_env_vbles		**env_vbles;

	start = *i;
	adjust_size = 0;
	if (state != NORMAL)
		start = ++(*i);
	env_vbles = NULL;
	while (line[*i] && (state != NORMAL || 
		(is_metachar(line[*i]) != SPACE_CHAR
		&& is_metachar(line[*i]) != METACHAR)))
	{
		if (line[*i] == '$' && state != SINGLE_QUOTES)
			if (!expand(line, i, &adjust_size, &env_vbles, state))
				return (NULL);
		if (line[*i] == '\'' || line[*i] =='\"')
			manage_quotes(&state, &adjust_size, line[*i]);
		(*i)++;
	}
	if (state != NORMAL)
		return (NULL);
	return (new_token(&line[start], (unsigned int)(*i - start - adjust_size),
		env_vbles));
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
		state = is_metachar(line[i]);
		if (state != METACHAR)
			token = get_token(line, &i, state);
		else
			token = new_token(&line[i++], 1, NULL);
		if (!add_to_list(list, token))
		{
			delete_list(list);
			return (NULL);
		}
	}
	return (list);
}
