/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:43:22 by rgallego          #+#    #+#             */
/*   Updated: 2023/07/19 16:47:19 by rgallego         ###   ########.fr       */
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
		return (mini_error(NULL, ALLOC_ERR, str));
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

void	ft_strrepl(char *str, char old_char, char new_char)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == old_char)
			str[i] = new_char;
		i++;
	}
}
