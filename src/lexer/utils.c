/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallego <rgallego@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:43:22 by rgallego          #+#    #+#             */
/*   Updated: 2023/08/22 10:38:25 by rgallego         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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


void	ft_strreplset(char *str, char *set, char new_char)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			str[i] = new_char;
		i++;
	}
}
