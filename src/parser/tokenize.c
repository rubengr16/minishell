/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/23 01:57:37 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	while ((*line)[*i] && (state != NORMAL || (get_state((*line)[*i]) != SPACE_CHAR
		&& get_state((*line)[*i]) != METACHAR)))
	{
		if ((*line)[*i] == '$' && state != SINGLE_QUOTES)
		{
			if (!expand(line, i,  state))
				return (NULL);
		}
		else if ((state == NORMAL && ((*line)[*i] == '\'' || (*line)[*i] =='\"'))
			|| (state == SINGLE_QUOTES && (*line)[*i] == (char)SINGLE_QUOTES)
			|| (state == DOUBLE_QUOTES && (*line)[*i] == (char)DOUBLE_QUOTES))
			manage_quotes(&state, i, &adjust_size, (*line)[*i]);
		else
			(*i)++;
	}
	if (state != NORMAL)
		return (NULL);
	return (new_token(&(*line)[start], *i - start - adjust_size, original_state));
}

static t_token	*get_metachar(char *line, unsigned int *i, enum e_state state)
{
	
	(*i)++;
	printf("char=%c, char2=%u\n", *line, *i);
	printf("line=%s\n", line);
	if (*line == '|' || (*line == '<' && line[*i] != '<')
		|| (*line == '>' && line[*i] != '>'))
		return new_token(line, 1, state);
	(*i)++;
	return new_token(line, 2, state);
}
echo"$SHLVL"=$SHLVL='$SHLVL' ><"|"
t_token_list	*tokenize(char **line)
{
	t_token_list	*list;
	t_token			*token;
	unsigned int	i;
	enum e_state	state;

	i = 0;
	list = create_list();
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
			token = get_metachar(*line, &i, state);
		if (!add_to_list(list, token))
		{
			delete_list(list);
			return (NULL);
		}
	}
	return (list);
}
