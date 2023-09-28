/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:18:57 by rgallego          #+#    #+#             */
/*   Updated: 2023/09/05 19:54:07 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static unsigned int	cnt_quotes(char *line)
{
	unsigned int	quotes_cnt;
	unsigned int	i;

	quotes_cnt = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == TRANS_SINGLE_Q || line[i] == TRANS_DOUBLE_Q)
			quotes_cnt++;
		i++;
	}
	return (quotes_cnt);
}

static char	*delete_quotes_trans(char **token)
{
	char			*aux;
	unsigned int	i;
	unsigned int	j;

	aux = malloc(sizeof(char) * (ft_strlen(*token) - cnt_quotes(*token) + 1));
	if (!aux)
		return (mini_error(NULL, NULL, SYS_ERR, NULL));
	i = 0;
	j = 0;
	while ((*token)[i])
	{
		if ((*token)[i] != TRANS_SINGLE_Q && (*token)[i] != TRANS_DOUBLE_Q)
			aux[j++] = (*token)[i];
		i++;
	}
	aux[j] = '\0';
	free(*token);
	return (aux);
}

char	*get_real_token(char *token, unsigned int is_redir)
{
	char			*aux;
	enum e_state	state;
	unsigned int	i;

	state = NORMAL;
	i = 0;
	aux = token;
	token = ft_strdup(token);
	if (!is_redir)
		free(aux);
	while (token && token[i])
	{
		if (token[i] == TRANS_DOUBLE_Q && state == NORMAL)
			state = DOUBLE_QUOTE;
		else if (token[i] == TRANS_DOUBLE_Q && state == DOUBLE_QUOTE)
			state = NORMAL;
		else if (token[i] == TRANS_DOLLAR && ++i)
			token = expand(&token, &i, state, is_redir);
		i++;
	}
	if (!token)
		return (NULL);
	aux = delete_quotes_trans(&token);
	return (aux);
}
