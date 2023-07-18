/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: socana-b <socana-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:43:22 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/18 19:40:00 by socana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

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
		return (mini_error(NULL, ALLOC_ERR));
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

enum e_token_type	get_token_type(char *token, enum e_state state)
{
	size_t	len;

	len = ft_strlen(token);
	if (state == METACHAR && !ft_strncmp("|", token, len))
		return (PIPE);
	if (state == METACHAR && !ft_strncmp("<", token, len))
		return (R_IN);
	if (state == METACHAR && !ft_strncmp("<<", token, len))
		return (R_IN_HERE_DOC);
	if (state == METACHAR && !ft_strncmp(">", token, len))
		return (R_OUT);
	if (state == METACHAR && !ft_strncmp(">>", token, len))
		return (R_OUT_APPEND);
	return (OTHER);
}
