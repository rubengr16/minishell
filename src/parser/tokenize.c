/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/29 18:59:04 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	manage_quotes(enum e_state *state, unsigned int *i,
	unsigned int *adjust_size, char c)
{
	(*i)++;
	(*adjust_size)++;
	if (*state != NORMAL)
		*state = NORMAL;
	else if (c == (char)SINGLE_QUOTE)
		*state = SINGLE_QUOTE;
	else if (c == (char)DOUBLE_QUOTE)
		*state = DOUBLE_QUOTE;
}

static t_token	*get_metachar(char *line, unsigned int *i, enum e_state state)
{
	unsigned int	adjust_size;

	adjust_size = 1;
	if ((*line == '<' && line[1] == '<') || (*line == '>' && line[1] == '>'))
		adjust_size = 2;
	*i += adjust_size;
	return (new_token(line, adjust_size, state));
}

static t_token	*get_token(char **line, unsigned int *i, enum e_state state)
{
	enum e_state	original_state;
	unsigned int	start;
	unsigned int	adjust_size;

	original_state = state;
	start = *i;
	adjust_size = 0;
	if (state != NORMAL)
		start = ++(*i);
	while (is_end_of_token((*line)[*i], state))
	{
		if ((*line)[*i] == '$' && state != SINGLE_QUOTE)
		{
			if (!expand(line, i, state))
				return (NULL);
		}
		else if (is_true_quote((*line)[*i], state))
			manage_quotes(&state, i, &adjust_size, (*line)[*i]);
		else
			(*i)++;
	}
	if (state != NORMAL)
		return (mini_error(NULL, UNCLOSED_Q_ERR));
	return (new_token(&(*line)[start], *i - start - adjust_size,
		original_state));
}

t_token_list	*tokenize(char **line)
{
	t_token_list	*list;
	t_token			*token;
	unsigned int	i;
	enum e_state	state;

	i = 0;
	list = create_token_list();
	if (!list)
		return (NULL);
	while ((*line)[i])
	{
		while ((*line)[i] == ' ')
			i++;
		state = get_state((*line)[i]);
		if (state != METACHAR)
			token = get_token(line, &i, state);
		else
			token = get_metachar(&(*line)[i], &i, state);
		if (!add_to_token_list(list, token))
		{
			delete_token_list(list, 1);
			return (NULL);
		}
	}
	free(*line);
	return (list);
}
