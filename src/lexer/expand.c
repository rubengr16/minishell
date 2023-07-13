/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:23:46 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/13 23:49:35 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

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
	{
		free(*line);
		return (mini_error(NULL, ALLOC_ERR, NULL));
	}
	(*i)--;
	ft_strlcpy(aux, *line, ft_strlen_to(*line, &(*line)[*i]) + 1);
	ft_strlcpy(&aux[*i], vble, ft_strlen(vble) + 1);
	ft_strlcpy(&aux[*i + ft_strlen(vble)], &(*line)[*i + 1 + name_len],
		ft_strlen(&(*line)[*i + 1 + name_len]) + 1);
	free(*line);
	*line = aux;
	*i = *i + ft_strlen(vble) - 1;
	return (*line);
}

char	*expand(char **line, unsigned int *i, enum e_state state,
	unsigned int is_redir)
{
	char			*vble;
	char			*name;
	unsigned int	name_len;

	(*i)++;
	name_len = 0;
	while ((*line)[*i + name_len] && (*line)[*i + name_len] != TRANS_SINGLE_Q
		&& (*line)[*i + name_len] != TRANS_DOUBLE_Q
		&& (*line)[*i + name_len] != TRANS_DOLLAR)
		name_len++;
	if (!name_len)
		return (vble_cpy(line, "$", i, 0));
	name = malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (mini_error(NULL, ALLOC_ERR, *line));
	ft_strlcpy(name, &((*line)[*i]), name_len + 1);
	vble = getenv(name);
	free(name);
	if (!vble)
		return (vble_cpy(line, "", i, name_len));
	if (ft_strchr(vble, ' ') && state == NORMAL && is_redir)
		return (mini_error(NULL, AMBIGUOUS_REDIR, NULL));
	return (vble_cpy(line, vble, i, name_len));
}
