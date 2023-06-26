/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:23:46 by rgallego          #+#    #+#             */
/*   Updated: 2023/06/26 21:56:59 by rgallego         ###   ########.fr       */
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

static char	*vble_cpy(char **line, char *vble, unsigned int *i,
	unsigned int name_len)
{
	char			*aux;
	unsigned int	total_len;

	total_len = ft_strlen(*line) - (name_len + 1) + ft_strlen(vble) + 1;
	aux = malloc(sizeof(char) * total_len);
	if (!aux)
		return mini_error(ALLOC_ERR);
	(*i)--;
	ft_strlcpy(aux, *line, ft_strlen_to(*line, &(*line)[*i]) + 1);
	ft_strlcpy(&aux[*i], vble, ft_strlen(vble) + 1);
	ft_strlcpy(&aux[*i + ft_strlen(vble)], &(*line)[*i + 1 + name_len],
		ft_strlen(&(*line)[*i + 1 + name_len]) + 1);
	free(*line);
	*line = aux;
	*i = *i + ft_strlen(vble);
	return (*line);
}

char *expand(char **line, unsigned int *i, enum e_state state)
{
	char			*aux;
	char			*name;
	unsigned int	name_len;

	(*i)++;
	name_len = 0;
	while (is_end_of_vble((*line)[*i + name_len], state))
		name_len++;
	if (!name_len)
		return (vble_cpy(line, "$", i, 0));
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return mini_error(ALLOC_ERR);
	ft_strlcpy(name, &((*line)[*i]), name_len + 1);
	aux = getenv(name);
	free(name);
	if (!aux)
		return (vble_cpy(line, "", i, name_len));
	return (vble_cpy(line, aux, i, name_len));
}
