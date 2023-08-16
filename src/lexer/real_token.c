/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:18:57 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/16 19:11:45 by socana-b         ###   ########.fr       */
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

static char	*delete_quotes_trans(char **token, unsigned int is_redir)
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
	if (!is_redir)
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
	while (token && token[i])
	{
		if (token[i] == TRANS_DOUBLE_Q && state == NORMAL)
			state = DOUBLE_QUOTE;
		else if (token[i] == TRANS_DOUBLE_Q && state == DOUBLE_QUOTE)
			state = NORMAL;
		else if (token[i] == TRANS_DOLLAR)
			token = expand(&token, &i, state, is_redir);
		i++;
	}
	if (!token)
		return (NULL);
	aux = delete_quotes_trans(&token, is_redir);
	ft_strrepl(aux, TRANS_VBLE_SPACE, ' ');
	token = aux;
	return (token);
}
