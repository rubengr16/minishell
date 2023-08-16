/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:23:46 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 16:29:01 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static size_t	ft_strlen_to(const char *s, const char *to)
{
	size_t	len;

	len = 0;
	while (s[len] && &s[len] != to)
		len++;
	return (len);
}

static unsigned int	ft_vble_len(char *line)
{
	unsigned int	len;

	len = 0;
	if (line[len] == '?')
		return (1);
	while (line[len] && line[len] != TRANS_SINGLE_Q
		&& line[len] != TRANS_DOUBLE_Q
		&& line[len] != TRANS_DOLLAR
		&& line[len] != ' ' && (len || (!len && line[len] != '?'))
		&& (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	return (len);
}

char	*vble_cpy(char **line, char *vble, unsigned int *i,
	unsigned int len)
{
	char			*aux;
	unsigned int	total_len;
	unsigned int	is_last_status;

	is_last_status = ((*line) && (*line)[*i] == '?');
	total_len = ft_strlen(*line) - (len + 1) + ft_strlen(vble) + 1;
	aux = malloc(sizeof(char) * total_len);
	if (!aux)
	{
		free(*line);
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	}
	(*i)--;
	ft_strlcpy(aux, *line, ft_strlen_to(*line, &(*line)[*i]) + 1);
	ft_strlcpy(&aux[*i], vble, ft_strlen(vble) + 1);
	ft_strlcpy(&aux[*i + ft_strlen(vble)], &(*line)[*i + 1 + len],
		ft_strlen(&(*line)[*i + 1 + len]) + 1);
	free(*line);
	*line = aux;
	*i = *i + ft_strlen(vble) - 1;
	if (is_last_status)
		free(vble);
	return (*line);
}

char	*expand(char **line, unsigned int *i, enum e_state state,
	unsigned int is_redir)
{
	char			*vble;
	char			*aux;
	unsigned int	len;

	(*i)++;
	len = ft_vble_len(&(*line)[*i]);
	if (!len && (*line)[*i] != TRANS_SINGLE_Q && (*line)[*i] != TRANS_DOUBLE_Q)
		return (vble_cpy(line, "$", i, 0));
	else if (!len
		&& ((*line)[*i] == TRANS_SINGLE_Q || (*line)[*i] == TRANS_DOUBLE_Q))
		return (vble_cpy(line, "", i, len));
	aux = malloc(sizeof(char) * (len + 1));
	if (!aux)
		return (mini_error(NULL, NULL, SYS_ERR, *line));
	ft_strlcpy(aux, &((*line)[*i]), len + 1);
	vble = get_env(aux);
	free(aux);
	if (!vble)
		return (vble_cpy(line, "", i, len));
	if (ft_strchr(vble, ' ') && state == NORMAL && is_redir)
		return (mini_error(AMBIG_REDIR_MSG, NULL, AMBIG_ERR, NULL));
	if (ft_strchr(vble, ' ') && state == NORMAL && !is_redir)
		ft_strrepl(vble, ' ', TRANS_VBLE_SPACE);
	aux = vble_cpy(line, vble, i, len);
	return (aux);
}
