/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:01:54 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/20 02:45:08 by rgallego         ###   ########.fr       */
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

int	add_vble(t_env_vbles ***env_vble, t_env_vbles	*vble)
{
	int			i;
	t_env_vbles	**aux_env;

	i = 0;
	aux_env = *env_vble;
	if (aux_env)
		while (aux_env[i])
			i++;
	*env_vble = malloc(sizeof(t_env_vbles *) * (i + 2));
	if (!env_vble)
		return (0);
	i = 0;
	if (aux_env)
	{
		while (aux_env[i])
		{
			*env_vble[i] = aux_env[i];
			i++;
		}
	}
	(*env_vble)[i] = vble;
	(*env_vble)[i + 1] = NULL;
	i = 0;
	if (aux_env)
	{
		while (aux_env[i])
			free(aux_env[i++]);
		free(*aux_env);
	}
	return (1);
}

int	expand(char *line, unsigned int *i, int *adjust_size,
	t_env_vbles ***env_vbles, enum e_state state)
{
	t_env_vbles	*vble;
	char		*name;

	(*i)++;
	vble = malloc(sizeof(t_env_vbles));
	if (!vble)
		return (0);
	vble->len = 0;
	while (line[*i + vble->len] && line[*i + vble->len] != ' '
		&& line[*i + vble->len] != '\"'
		&& (state == DOUBLE_QUOTES 
		|| (is_metachar(line[*i + vble->len]) != METACHAR
		&& line[*i + vble->len] != '\'')))
		vble->len++;
	name = malloc(sizeof(char) * (vble->len + 1));
	if (!name)
		return (0);
	ft_strlcpy(name, &line[*i], vble->len + 1);
	vble->value = ft_strdup(getenv(name));
	if (!vble->value)
		vble->value = name;
	else
		free(name);
	*i += vble->len;
	printf("len value: %ld\n", ft_strlen(vble->value));
	printf("len: %d\n", vble->len);
	*adjust_size -= (ft_strlen(vble->value) - vble->len - 1);
	vble->len = ft_strlen(vble->value);
	return (add_vble(env_vbles, vble));
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
		printf("%s\n", &line[*i]);
		(*i)++;
	}
	if (state != NORMAL)
		return (NULL);
	printf("%d\n", *i - start - adjust_size);
	printf("%d\n", *i);
	printf("%d\n", start);
	printf("%d\n", adjust_size);
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
