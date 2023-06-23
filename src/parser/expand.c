/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:23:46 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/23 01:59:57 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_strlen_to(const char *s, const char *to)
{
	size_t	len;

	len = 0;
	while (s[len] && &s[len] != to)
		len++;
	return (len);
}

static int	vble_cpy(char **line, char *vble, unsigned int *i,
	unsigned int name_len)
{
	char			*aux;
	unsigned int	total_len;

	total_len = ft_strlen(*line) - (name_len + 1) + ft_strlen(vble) + 1;
	aux = malloc(sizeof(char) * total_len);
	if (!aux)
		return (0);
	(*i)--;
	ft_strlcpy(aux, *line, ft_strlen_to(*line, &(*line)[*i]) + 1);
	ft_strlcpy(&aux[*i], vble, ft_strlen(vble) + 1);
	ft_strlcpy(&aux[*i + ft_strlen(vble)], &(*line)[*i + 1 + name_len],
		ft_strlen(&(*line)[*i + 1 + name_len]) + 1);
	free(*line);
	*line = aux;
	*i = *i + ft_strlen(vble);
	return (1);
}

int	expand(char **line, unsigned int *i, enum e_state state)
{
	char			*aux;
	char			*name;
	unsigned int	name_len;

	(*i)++;
	name_len = 0;
	printf("%s\n", *line);
	while ((*line)[*i + name_len] && (*line)[*i + name_len] != ' '
		&& (*line)[*i + name_len] != '\"' && (state == DOUBLE_QUOTES
		|| (get_state((*line)[*i + name_len]) != METACHAR
		&& (*line)[*i + name_len] != '\'')))
		name_len++;
	if (!name_len)
		return (vble_cpy(line, "$", i, 0));
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (0);
	ft_strlcpy(name, &((*line)[*i]), name_len + 1);
	aux = getenv(name);
	free(name);
	if (!aux)
		return (vble_cpy(line, "", i, name_len));
	return (vble_cpy(line, aux, i, name_len));
}
