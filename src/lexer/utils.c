/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:43:22 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/14 00:13:40 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	**add_to_char_double_ptr(char ***char_double_ptr, char *str)
{
	unsigned int	i;
	char			**aux;

	i = 0;
	if (*char_double_ptr)
		while ((*char_double_ptr)[i])
			i++;
	aux = malloc(sizeof(char *) * (i + 2));
	if (!aux)
		return (mini_error(NULL, ALLOC_ERR, NULL));
	i = 0;
	if (*char_double_ptr)
	{
		while ((*char_double_ptr)[i])
		{
			aux[i] = (*char_double_ptr)[i];
			i++;
		}
	}
	aux[i] = str;
	aux[i + 1] = NULL;
	free(*char_double_ptr);
	*char_double_ptr = aux;
	return (*char_double_ptr);
}

enum e_token_type	get_token_type(char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (!ft_strncmp("|", token, len))
		return (PIPE);
	if (!ft_strncmp("<", token, len))
		return (R_IN);
	if (!ft_strncmp("<<", token, len))
		return (R_IN_HERE_DOC);
	if (!ft_strncmp(">", token, len))
		return (R_OUT);
	if (!ft_strncmp(">>", token, len))
		return (R_OUT_APPEND);
	return (OTHER);
}

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
		return (mini_error(NULL, ALLOC_ERR, NULL));
	i = 0;
	j = 0;
	while ((*token)[i])
	{
		if ((*token)[i] != TRANS_SINGLE_Q && (*token)[i] != TRANS_DOUBLE_Q)
			aux[j++] = (*token)[i++];
		else
			i++;
	}
	aux[i] = '\0';
	return (aux);
}

char	*get_real_token(char *token, unsigned int is_redir)
{
	char			*aux;
	enum e_state	state;
	unsigned int	i;

	state = NORMAL;
	i = 0;
	while (*token && token[i])
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
	aux = delete_quotes_trans(&token);
	free(token);
	token = aux;
	return (token);
}
