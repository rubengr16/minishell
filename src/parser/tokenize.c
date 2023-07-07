/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/07 18:47:00 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	translate_quotes(char *line, unsigned int i)
{
	if (line[i] == '\'')
		return (TRANS_SINGLE_Q);
	return (TRANS_DOUBLE_Q);
}

static void	manage_quotes(char *line, enum e_state *state, unsigned int *i)
{
	if (*state != NORMAL)
		*state = NORMAL;
	else if (line[*i] == (char)SINGLE_QUOTE)
		*state = SINGLE_QUOTE;
	else if (line[*i] == (char)DOUBLE_QUOTE)
		*state = DOUBLE_QUOTE;
	line[*i] = translate_quotes(line, *i);
}

static t_token	*get_metachar(char *line, unsigned int *i, enum e_state state)
{
	unsigned int	size;

	size = 1;
	if ((*line == '<' && line[1] == '<') || (*line == '>' && line[1] == '>'))
		size = 2;
	*i += size;
	return (new_token(line, size, state));
}

static t_token	*get_token(char **line, unsigned int *i, enum e_state state)
{
	enum e_state	original_state;
	unsigned int	start;

	original_state = state;
	start = *i;
	if (state != NORMAL)
		(*line)[*i] = translate_quotes(*line, *i);
	while (is_end_of_token((*line)[*i], state))
	{
		if ((*line)[*i] == '$' && state != SINGLE_QUOTE)
			while (is_end_of_vble((*line)[*i], state))
				(*i)++;
		else 
		{
			if (is_true_quote((*line)[*i], state))
				manage_quotes(*line, &state, i);
			(*i)++;
		}
	}
	if (state != NORMAL)
		return (mini_error(NULL, UNCLOSED_Q_ERR));
	return (new_token(&(*line)[start], *i - start, original_state));
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
			delete_token_list(&list, 1);
			return (NULL);
		}
	}
	free(*line);
	return (list);
}
